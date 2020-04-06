#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#include "../libopencm3/include/libopencm3/stm32/adc.h"
#include "../libopencm3/include/libopencm3/stm32/gpio.h"
#include "../libopencm3/include/libopencm3/stm32/timer.h"
#include "../libopencm3/include/libopencm3/stm32/dma.h"
#include "../libopencm3/include/libopencm3/stm32/rcc.h"
#include "../libopencm3/include/libopencm3/cm3/scb.h"
#include "../libopencm3/include/libopencm3/cm3/nvic.h"
#include "measure.h"
#include "tl.h"
#include "display.h"

// 512 = 100 кГц на выходе
#define DIVIDER 768
volatile tlParams tlPar = {DIVIDER, // number of timer counts per one period
                                    // (fTim = 48mHz)
                           2000,    // maximum voltage (volts*100)
                           300,     // minimum voltage
                           700,     // maximum curent (amperes*100)
                           100,     // minimum current
                           (80*DIVIDER)/100, // max duty cycle (if too big
                                             // rail breakdown is possible)
                           (1*DIVIDER)/100,  // min dut cycle (if 0 indeterminate
                                             // behavior)
                           0,       // mean voltage (userful for the display)
                           0,       // mean current
                           1700,       // voltage which the regulator is trying to set
                           1000,     // curent which the regulator is trying to set
                           100,     // voltage which is measured instantly
                           100,     // current which is measured instantly
                           (1*DIVIDER)/100, // current duty cycle
                           0
                        };

// userful only for regulFormula function
volatile struct pidrr {
    const int32_t k;
    const int32_t i;
    const int32_t d;
    const int32_t t;
    int32_t u;
    int32_t u1;
    int32_t e;
    int32_t e1;
} pidr = {10,
          5,
          2,
          1, 0, 0, 0, 0};
extern volatile adcDma measures;

const uint32_t clockOnSeq     = 0x00000003;
const uint32_t clockOffSeq[2] = {0xfffe0000, 0xfffd0000};

void clockInit(void);
void clockDeInit(void);
void feedBack(void);
int32_t regulFormula(int32_t e);


int32_t regulFormula(int32_t err)
{
    pidr.e = err;
    pidr.e1 = pidr.e;
    pidr.u1 = pidr.u;
    int32_t sl1 = pidr.k*pidr.e;
    int32_t sl2 = pidr.i*(pidr.u1 + pidr.e*pidr.t);
    int32_t sl3 = pidr.d*(pidr.e - pidr.e1);
    pidr.u  = (sl1 + sl2 + sl3) / 1000;
    return pidr.u;
}


void clockDeInit()
{
    //сброс
    TIM3_ARR = (uint32_t)0;
    PWM_BORDER = (uint32_t)0;
    TIM3_DIER = (uint32_t)0;
    TIM3_CR1 = (uint32_t)0;
    DMA1_CPAR4 = (uint32_t)0;
    DMA1_CMAR4 = (uint32_t)0;
    DMA1_CNDTR4 = (uint32_t)0;
}


void clockInit()
{
    // установка
    uint32_t timEn = (uint32_t)(TIM_CR1_CKD_CK_INT | TIM_CR1_CEN);
    TIM3_ARR  = (uint32_t)tlPar.divider;
    TIM3_DIER  = (uint32_t)(TIM_DIER_CC1DE | TIM_DIER_UDE);

    uint32_t dmaUpEn = (uint32_t)(DMA_CCR_MINC | DMA_CCR_MSIZE_32BIT | \
                                  DMA_CCR_PSIZE_32BIT | DMA_CCR_PL_VERY_HIGH | \
                                  DMA_CCR_DIR | DMA_CCR_CIRC | \
                                  DMA_CCR_TEIE | DMA_CCR_EN | \
                                  DMA_CCR_PL_VERY_HIGH);
    uint32_t dmaCrEn = (uint32_t)(DMA_CCR_MINC | DMA_CCR_MSIZE_32BIT | \
                                  DMA_CCR_PSIZE_32BIT | DMA_CCR_PL_VERY_HIGH | \
                                  DMA_CCR_DIR | DMA_CCR_CIRC | \
                                  DMA_CCR_TEIE | DMA_CCR_EN | \
                                  DMA_CCR_PL_HIGH);
    // DMA по update event
    DMA1_CPAR4  = (uint32_t) &GPIOF_BSRR;
    DMA1_CMAR4  = (uint32_t) &clockOnSeq;
    DMA1_CNDTR4 = (uint32_t) 1;
    // DMA по compare event
    DMA1_CPAR3  = (uint32_t) &GPIOF_BSRR;
    DMA1_CMAR3  = (uint32_t) clockOffSeq;
    DMA1_CNDTR3 = (uint32_t) 2;

    TIM3_CR1 = timEn;
    DMA1_CCR4 = dmaUpEn;
    DMA1_CCR3 = dmaCrEn;
    TIM3_EGR |= TIM_EGR_UG;
    nvic_enable_irq(NVIC_DMA1_CHANNEL4_7_DMA2_CHANNEL3_5_IRQ); // прерывание для ошибок
}


void tlInit()
{
    // лапки выходов
    RCC_AHBENR |= TLOUT_RCC_EN;
    gpio_mode_setup(TLOUT_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, TL1OUT_PIN | TL2OUT_PIN);
    gpio_set_output_options(TLOUT_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, TL1OUT_PIN | TL2OUT_PIN);
    // клок периферии
    RCC_APB1ENR |= RCC_APB1ENR_TIM3EN;
    RCC_AHBENR |= RCC_AHBENR_DMA1EN;
    // собсна сам ШИМ
    PWM_BORDER = tlPar.minDuty;
    clockInit();
    // инициализация измерений температуры, тока и напряжения, а еще переменника
    measureInit();
}

// homebrew mutex
void tlLock()
{
    tlPar.lockFlag = 1;
    if( ADC1_ISR & ADC_ISR_EOSEQ ) ADC1_ISR |= ADC_ISR_EOSEQ;
    ADC1_IER = (uint32_t)0;
    ADC1_CR |= ADC_CR_ADSTP;
    PWM_BORDER = tlPar.minDuty;
    GPIOF_BSRR = 0xffff0000;
    DMA1_CCR1 &= ~((uint32_t)DMA_CCR_EN);
    DMA1_CCR2 &= ~((uint32_t)DMA_CCR_EN);
    DMA1_CCR3 &= ~((uint32_t)DMA_CCR_EN);
    DMA1_CCR4 &= ~((uint32_t)DMA_CCR_EN);
}



void tlUnlock()
{
    if( tlPar.lockFlag == 0 ) return;
    DMA1_CNDTR1 = (uint32_t) ADC_NUMBER;
    DMA1_CNDTR2 = (uint32_t) 3;
    DMA1_CNDTR3 = (uint32_t) 2;
    DMA1_CNDTR4 = (uint32_t) 1;
    DMA1_CCR1 |= DMA_CCR_EN;
    DMA1_CCR2 |= DMA_CCR_EN;
    DMA1_CCR3 |= DMA_CCR_EN;
    DMA1_CCR4 |= DMA_CCR_EN;

    ADC1_ISR = 0xffffffff;
    ADC1_IER = ADC_IER_EOSIE;
    if( ADC1_CR & ADC_CR_ADSTART ) {
        ADC1_CR |= ADC_CR_ADSTP;
    }
    uint32_t timeout = 1e5;
    while( (ADC1_CR & ADC_CR_ADSTART) && (--timeout > 0) );
    ADC1_CR |= ADC_CR_ADSTART;
    tlPar.lockFlag = 0;
}

void setDuty(int32_t duty)
{
    tlPar.duty = duty;
    if( tlPar.duty > tlPar.maxDuty ) {
        tlPar.duty = tlPar.maxDuty;
    } else if( tlPar.duty < tlPar.minDuty ) {
        tlPar.duty = tlPar.minDuty;
    }
    PWM_BORDER = tlPar.duty;
}

void fault()
{
    // таймер ШИМ
    TIM3_CR1 = (uint32_t)0;
    // порты
    GPIOF_BSRR = 0xffff0000;
    myprintf("fuc");
    // перезагрузка контроллера целиком
    scb_reset_system();
}

volatile int32_t e[100];
volatile int32_t f[3];
void feedBack()
{
    static int i = 0;
    tlPar.current = getAmps();
    tlPar.voltage = getVoltage();
    if( ( tlPar.current > CURRENT_LIMIT ) || \
        ( tlPar.voltage > VOLTAGE_LIMIT ) || \
        ( getTemperature() > TEMP_LIMIT ) )
    {
        f[0] = tlPar.current;
        f[1] = tlPar.voltage;
        f[2] = getTemperature();
        fault();
    }
    tlPar.meanCurrent = (tlPar.meanCurrent + tlPar.current) / 2;
    tlPar.meanVoltage = (tlPar.meanVoltage + tlPar.voltage) / 2;
//    e[i++] = tlPar.voltage;

    int32_t voltErr = (int32_t)tlPar.setVoltage - (int32_t)tlPar.voltage;
    int32_t currErr = (int32_t)tlPar.setCurrent - (int32_t)tlPar.current;
    int32_t minErr = currErr;
    if( voltErr < currErr ) {
        minErr = voltErr;
    }
    e[i] = regulFormula(minErr);
    if( ++i > 100 ) i = 0;
    setDuty(tlPar.duty += regulFormula(minErr));
}

void adc_comp_isr()
{
    ADC1_ISR |= ADC_ISR_EOSEQ;
//    feedBack();
}

// при любой ошибке перезагружайся
void dma1_channel1_isr()
{
    fault();
}

void dma1_channel2_3_dma2_channel1_2_isr()
{
    fault();
}

void dma1_channel4_7_dma2_channel3_5_isr()
{
    fault();
}

void spi1_isr(void)
{
    fault();
}

void flash_isr()
{
    fault();
}
