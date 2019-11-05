#include <stdint.h>
#include "menu.h"
#include "display.h"
#include "board.h"
#include "charger.h"
#include "tl.h"
#include "../libopencm3/include/libopencm3/stm32/rcc.h"
#include "../libopencm3/include/libopencm3/stm32/pwr.h"
#include "../libopencm3/include/libopencm3/stm32/rtc.h"
#include "../libopencm3/include/libopencm3/stm32/spi.h"
#include "../libopencm3/include/libopencm3/stm32/gpio.h"
#include "../libopencm3/include/libopencm3/stm32/dma.h"
#include "../libopencm3/include/libopencm3/stm32/timer.h"
#include "../libopencm3/include/libopencm3/stm32/exti.h"
#include "../libopencm3/include/libopencm3/cm3/scb.h"
#include "../libopencm3/include/libopencm3/cm3/nvic.h"

extern volatile tlParams tlPar;
extern volatile uint32_t dispBuffer[DIGITS];
volatile uint32_t buttons = 0xffffffff;
volatile uint8_t checkCnt = 0;

void rtcInit(void);
void buttonDelay(void);

void clkInit()
{
    // не знаю зачем, на всякий случай
    RCC_CR2  |= RCC_CR2_HSI14ON;
    // такирование от встроенных RC генераторов, SYS 48 МГц, AHB 48МГц, APB 24 МГц
    uint32_t timeout = 9e6;
    if ( (RCC_CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL )
    {
        RCC_CFGR &= ~RCC_CFGR_SW;
        while ( ((RCC_CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI) || \
                (--timeout > 1) );
    }
    RCC_CFGR |= RCC_CFGR_PLLSRC_HSI_CLK_DIV2;
    RCC_CR &= (uint32_t)(~RCC_CR_PLLON);
    timeout = 9e6;
    while( ((RCC_CR & RCC_CR_PLLRDY) != 0) && (--timeout > 1) );
    RCC_CFGR &= ~RCC_CFGR_PLLMUL;
    RCC_CFGR |= RCC_CFGR_PLLMUL_MUL12;
    RCC_CR |= RCC_CR_PLLON;
    timeout = 9e6;
    while( ((RCC_CR & RCC_CR_PLLRDY) == 0) && (--timeout > 1) );
    RCC_CFGR |= (uint32_t) (RCC_CFGR_SW_PLL);
    timeout = 9e6;
    while ( ((RCC_CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) && (--timeout > 1) );
    RCC_CFGR |= (uint32_t) RCC_CFGR_HPRE_NODIV | RCC_CFGR_PPRE_DIV2;
    RCC_CSR  |= (uint32_t) RCC_CSR_LSION;
    timeout = 9e6;
    while ( ((RCC_CSR & RCC_CSR_LSIRDY) == 0 ) && (--timeout > 0) );
}


void displayInit()
{
    // сперва порты
    RCC_AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;
    gpio_mode_setup(DISPLAY_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, CLOCK_PIN | DATA_PIN);
    gpio_set_output_options(DISPLAY_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, CLOCK_PIN | DATA_PIN);
    gpio_set_af(DISPLAY_PORT, GPIO_AF0, CLOCK_PIN | DATA_PIN);
    gpio_mode_setup(DISPLAY_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, NSS_NC);
    gpio_set_output_options(DISPLAY_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, NSS_NC);
    gpio_set_af(DISPLAY_PORT, GPIO_AF0, NSS_NC);
    gpio_mode_setup(DISPLAY_EN_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, EN_PIN);
    gpio_set_output_options(DISPLAY_EN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, EN_PIN);
    gpio_set_af(DISPLAY_EN_PORT, GPIO_AF2, EN_PIN);
    // потом интерфейс
    RCC_APB2ENR |= RCC_APB2ENR_SPI1EN;
    uint32_t cr1 = SPI_CR1_BAUDRATE_FPCLK_DIV_2 | SPI_CR1_MSTR;
    cr1 |= (uint32_t)(SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE);
    SPI1_CR1 = cr1;
    SPI1_CR2  = (uint32_t)(SPI_CR2_DS_16BIT | SPI_CR2_ERRIE);
    nvic_enable_irq(NVIC_SPI1_IRQ);

    // передача каждого из символов и переключение лапки EN работает по таймеру
    RCC_APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1_CR1   = (uint32_t) TIM_CR1_CKD_CK_INT;
//    TIM1_CR2   = (uint32_t) TIM_CR2_CCDS;
    TIM1_PSC   = (uint32_t) 4;
    TIM1_ARR   = (uint32_t) 1024;
    TIM1_CCR3  = (uint32_t) 2;
    TIM1_CCR1  = (uint32_t) 512;
    TIM1_DIER  = (uint32_t) TIM_DIER_CC1DE;
    TIM1_CCER  = (uint32_t) TIM_CCER_CC3NE;
    TIM1_CCMR2 = (uint32_t) (TIM_CCMR2_OC3M_PWM2 | TIM_CCMR2_OC3PE);
    TIM1_BDTR  = (uint32_t) TIM_BDTR_MOE;
    TIM1_CR1  |= (uint32_t) TIM_CR1_CEN;

    // в который раз уже DMA включаю, тут все понятно
    RCC_AHBENR |= RCC_AHBENR_DMA1EN;
    DMA1_CPAR2  = (uint32_t) &SPI1_DR;
    DMA1_CMAR2  = (uint32_t) &dispBuffer;
    DMA1_CNDTR2 = (uint32_t) 3;
    // конфиг DMA
    uint32_t ccr = DMA_CCR_MINC | DMA_CCR_MSIZE_32BIT | DMA_CCR_PSIZE_32BIT;
    ccr |= DMA_CCR_PL_LOW | DMA_CCR_DIR | DMA_CCR_CIRC;
    ccr |= DMA_CCR_TEIE;
    DMA1_CCR2 = ccr;

    nvic_enable_irq(NVIC_DMA1_CHANNEL2_3_DMA2_CHANNEL1_2_IRQ);
    // понеслась
    SPI1_CR1  |= SPI_CR1_SPE;
    DMA1_CCR2 |= DMA_CCR_EN;
    TIM1_EGR  |= TIM_EGR_UG;
}


void rtcInit()
{
    // спиздил с инета, сам не вникал
    RCC_APB1ENR |= (uint32_t)RCC_APB1ENR_PWREN;
    pwr_disable_backup_domain_write_protect();
    rcc_set_rtc_clock_source(RCC_LSI);
    rcc_enable_rtc_clock();
    // тактирование от встроенного генератора 40 кГц
    rtc_unlock();
    rtc_set_prescaler(0x137, 0x7f);
    RTC_ISR |= (uint32_t)RTC_ISR_INIT;
    uint32_t timeout = 9e8;
    while( ((RTC_ISR & RTC_ISR_INITF) == 0) && (--timeout > 0) );
    // полночь, 1 января 2000
    uint32_t dr = 0;
    dr |= 0 << RTC_DR_YT_SHIFT;
    dr |= 0 << RTC_DR_YU_SHIFT;
    dr |= 6 << RTC_DR_WDU_SHIFT;
    dr |= 0 << RTC_DR_MT_SHIFT;
    dr |= 1 << RTC_DR_MU_SHIFT;
    dr |= 0 << RTC_DR_DT_SHIFT;
    dr |= 1 << RTC_DR_DU_SHIFT;
    RTC_TR = 0;
    RTC_DR = dr;
    RTC_ISR &= ~(RTC_ISR_INIT);
    rtc_lock();
}

void menuInit()
{
    // забыл удалить
//    gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO1);
//    gpio_set_output_options(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, GPIO1);
    // часы (помогут узнать сколько заряжается аккумулятор)
    rtcInit();
    // прерывания на кнопках
    // инициализация портов (подтяжка к +3.3, вход)
    RCC_AHBENR |= RCC_AHBENR_GPIOAEN;
    gpio_mode_setup(BUTTON_PORT, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, SET_PIN | CHOOSE_PIN);
    gpio_set_output_options(BUTTON_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, SET_PIN | CHOOSE_PIN);
    // конфиг прерываний по нажатию на кнопки
    exti_select_source(EXTI9, GPIOA);
    exti_select_source(EXTI10, GPIOA);
    exti_set_trigger(EXTI9 | EXTI10, EXTI_TRIGGER_FALLING);
    exti_enable_request(EXTI9 | EXTI10);
    EXTI_PR = 0xffffffff;
    nvic_enable_irq(NVIC_EXTI4_15_IRQ);
    nvic_set_priority(NVIC_EXTI4_15_IRQ, 0x40);
    EXTI_PR = 0xffffffff;
    // таймер антидребезга
    RCC_APB2ENR |= RCC_APB2ENR_TIM17EN;
    TIM17_CR1   = (uint32_t) TIM_CR1_CKD_CK_INT | TIM_CR1_ARPE | TIM_CR1_OPM;
    TIM17_PSC   = (uint32_t) 65535;
    TIM17_ARR   = (uint32_t) 3;
    TIM17_DIER  = (uint32_t) TIM_DIER_UIE;
    TIM17_EGR  |= (uint32_t) TIM_EGR_UG;
    TIM17_SR = 0;
    nvic_enable_irq(NVIC_TIM17_IRQ);
    nvic_set_priority(NVIC_TIM17_IRQ, 0x40);
    // таймер рендера меню, fps 15 Гц
    RCC_APB1ENR |= RCC_APB1ENR_TIM14EN;
    TIM14_CR1   = (uint32_t) TIM_CR1_CKD_CK_INT;
    TIM14_PSC   = (uint32_t) 65535;
    TIM14_ARR   = (uint32_t) 48;
    TIM14_DIER  = (uint32_t) TIM_DIER_UIE;
    TIM14_CR1  |= (uint32_t) TIM_CR1_CEN;
    TIM14_EGR  |= (uint32_t) TIM_EGR_UG;
    TIM14_SR = 0;
    nvic_enable_irq(NVIC_TIM14_IRQ);
    nvic_set_priority(NVIC_TIM14_IRQ, 0x00);
    catchTime();
}

void fanInit()
{
    // лапа
    RCC_AHBENR |= RCC_AHBENR_GPIOAEN;
    gpio_mode_setup(FAN_PORT, GPIO_MODE_AF, GPIO_PUPD_NONE, FAN_PIN);
    gpio_set_output_options(FAN_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, FAN_PIN);
    gpio_set_af(FAN_PORT, GPIO_AF5, FAN_PIN);
    // таймер с ШИМом
    RCC_APB2ENR |= RCC_APB2ENR_TIM16EN;
    TIM16_CR1   = (uint32_t) TIM_CR1_CKD_CK_INT;
    TIM16_PSC   = (uint32_t) 0;
    TIM16_ARR   = (uint32_t) 127;
    TIM16_CCR1  = (uint32_t) 63;
    TIM16_CCMR1 = (uint32_t) TIM_CCMR1_OC1M_PWM1;
    TIM16_CCER  = (uint32_t) TIM_CCER_CC1E;
    TIM16_BDTR  = (uint32_t) TIM_BDTR_MOE;
    TIM16_CR1  |= (uint32_t) TIM_CR1_CEN;
    TIM16_EGR  |= (uint32_t) TIM_EGR_UG;
}

void fanUpdate()
{
    // даже если блок ничего не выдает, вентилятор работает от 6В
    const uint32_t minimum = 50;
    const uint32_t maximum = 50;
    const uint32_t coef = 12 * 128;
    uint32_t power = tlPar.setVoltage * tlPar.setCurrent / 10000;
    // начиная от 50 ватт вентилятор вращается на полную
    if( power > maximum ) power = maximum;
    // поправка на то, что вентилятор запитан от этого же блока питания,
    // напряжение которого меняется (максимум 12В на вентилятор)
    uint32_t ccr = ((minimum + power) * coef) / tlPar.voltage;
    if( ccr > 127 ) ccr = 127;
    TIM16_CCR1 = ccr;
}

void exti4_15_isr(void)
{
    exti_disable_request(EXTI9 | EXTI10);
    EXTI_PR = 0xffffffff;
    buttons = BUTTON_READ;
    checkCnt = 0;
    TIM17_SR = 0;
    TIM17_CR1 |= (uint32_t) TIM_CR1_CEN;
}

void tim17_isr()
{
    const uint8_t nCheck = 3;

    TIM17_SR = 0;
    uint32_t read = BUTTON_READ;
    buttons |= read;
    if(checkCnt++ < nCheck) {
        TIM17_CR1 |= (uint32_t) TIM_CR1_CEN;
        return;
    }

    if( (buttons & SET_PIN) == 0 ) {
        setButton();
    } else if( (buttons & CHOOSE_PIN) == 0 ) {
        currentVoltageButton();
    }

    EXTI_PR = 0xffffffff;
    exti_enable_request(EXTI9 | EXTI10);
}

void tim14_isr()
{
    TIM14_SR = 0;

    menu();
    // за одним вентилятор подкрутить
    fanUpdate();
}
