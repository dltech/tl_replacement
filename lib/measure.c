#include <stdint.h>
#include <limits.h>
//#include <math.h>
#include "../libopencm3/include/libopencm3/stm32/adc.h"
#include "../libopencm3/include/libopencm3/stm32/rcc.h"
#include "../libopencm3/include/libopencm3/stm32/dma.h"
#include "../libopencm3/include/libopencm3/cm3/nvic.h"
#include "../libopencm3/include/libopencm3/stm32/gpio.h"
#include "measure.h"

/* Измерятор, измерения работают автоматом по DMA, по окончанию врубается
   прерывание. Прочитать результат можно из функций геттеров, все (ток, напряжение)
   умножены на 100. Температура строго в градусах, переменник в процентах (0-100)
*/

volatile adcDma measures = {0, 0, 0, 0, 0, 0};

uint32_t adcCal(void);
uint32_t measureVref(void);
uint32_t adcToVoltage(uint32_t input);

uint32_t adcCal()
{
    ADC1_CR = ADC_CR_ADCAL;
    uint32_t timeout = INT_MAX;
    while ( ((ADC1_CR & ADC_CR_ADCAL) != 0) && (--timeout > 1) );
    return ADC1_DR;
}

uint32_t measureVref()
{
    // Про калибровку ничего не написано (вернее про то, что делать с полученным
    // результатом). Потому ограничимся измерением опорного напряжения.
    RCC_APB2ENR |= RCC_APB2ENR_ADCEN;
    ADC1_CR = ADC_CR_ADEN;
    uint32_t timeout = INT_MAX;
    while ( ((ADC1_ISR & ADC_ISR_ADRDY) == 0) && (--timeout > 1) ) ;
    ADC1_CCR = (uint32_t) ADC_CCR_VREFEN;
    ADC1_CHSELR = (uint32_t) (1<<ADC_CHANNEL_VREF);
    ADC1_CFGR1 = (uint32_t)(ADC_CFGR1_OVRMOD | ADC_CFGR1_RES_12_BIT);
    ADC1_CFGR2 = (uint32_t) ADC_CFGR2_CKMODE_CK_ADC;
    ADC1_SMPR = (uint32_t)ADC_SMPR_SMP_239DOT5;

    uint32_t vRef = 0;
    uint32_t cnt = 0;
    timeout = INT_MAX;
    // измеряю пока хотя бы один вольт не покажет
    while( (vRef < 1000) && (cnt++ < 1e5) ) {
        ADC1_CR |= ADC_CR_ADSTART;
        timeout = INT_MAX;
        while( ((ADC1_ISR & ADC_ISR_EOC) == 0) && (--timeout > 1) );
        vRef = ADC1_DR;
    }
    timeout = INT_MAX;
    ADC1_CR |= ADC_CR_ADSTP;
    while ( ((ADC1_CR & ADC_CR_ADSTP) != 0) && (--timeout > 1) );
    timeout = INT_MAX;
    ADC1_CR |= ADC_CR_ADDIS;
    while ( ((ADC1_CR & ADC_CR_ADEN) != 0) && (--timeout > 1) );
    return vRef;
}

void adcDmaInit()
{
    // сопоставим адреса данных с ацп с структурой в памяти
    RCC_AHBENR |= RCC_AHBENR_DMA1EN;
    DMA1_CPAR1 = (uint32_t) &ADC1_DR;
    DMA1_CMAR1 = (uint32_t) &measures;
    DMA1_CNDTR1 = (uint32_t) ADC_NUMBER;
    // конфиг DMA
    uint32_t ccr =  DMA_CCR_MINC | DMA_CCR_MSIZE_32BIT | DMA_CCR_PSIZE_32BIT;
    ccr |= DMA_CCR_PL_MEDIUM | DMA_CCR_CIRC | DMA_CCR_TEIE | DMA_CCR_EN;
    DMA1_CCR1 = ccr;
}

void adcDmaDeinit()
{
    DMA1_CCR1 = (uint32_t)0;
    DMA1_CPAR1 = (uint32_t)0;
    DMA1_CMAR1 = (uint32_t)0;
    DMA1_CNDTR1 = (uint32_t)0;
}

void measureInit()
{
    // конфиг АЦП
    measureVref();
    adcCal();
    measures.vrefMeasured = measureVref();

    // прописать каналы, включить сенсор температуры
    ADC1_CR = ADC_CR_ADEN;
    uint32_t timeout = INT_MAX;
    while ( ((ADC1_ISR & ADC_ISR_ADRDY) == 0) && (--timeout > 1) ) ;
    ADC1_CCR = (uint32_t)(ADC_CCR_TSEN);// | ADC_CCR_VREFEN);
    ADC1_CHSELR = (uint32_t)ADC_CHANNELS;
    uint32_t cfgr = ADC_CFGR1_CONT | ADC_CFGR1_DMAEN | ADC_CFGR1_DMACFG;
    cfgr |= ADC_CFGR1_OVRMOD | ADC_CFGR1_RES_12_BIT;
    ADC1_CFGR1 = cfgr;
//    ADC1_CFGR1 &= ~(ADC_CFGR1_ALIGN | ADC_CFGR1_SCANDIR);
    ADC1_CFGR2 = (uint32_t) ADC_CFGR2_CKMODE_CK_ADC;
    // время считывания поставим побольше что бы не было ошибок
    // внутреннее сопротивление при этом 50кОм
    // время на одно измерение около 20 мкс
    ADC1_SMPR = (uint32_t) ADC_SMPR_SMP_239DOT5;
    // прерывание по окончанию измерения последовательности
    ADC1_IER = ADC_IER_EOSIE;

    // порты
    RCC_AHBENR |= RCC_AHBENR_GPIOAEN;
    gpio_mode_setup(MEASURE_PORT, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, MEASURE_PINS);
    // вкл DMA и АЦП
    ADC1_ISR = 0xffffffff;
    adcDmaInit();
    ADC1_CR |= ADC_CR_ADSTART;
    // приоритет измерений выше всех
    nvic_set_priority(NVIC_ADC_COMP_IRQ, 0xc0);
    nvic_enable_irq(NVIC_DMA1_CHANNEL1_IRQ);
    int cnt = 10;
    while( --cnt > 0 ) {
        timeout = 1e5;
        while( ((ADC1_ISR & ADC_ISR_EOSEQ) == 0) && (--timeout > 0) );
        ADC1_ISR = 0xffff;
    }
    nvic_enable_irq(NVIC_ADC_COMP_IRQ);
}

uint32_t adcToVoltage(uint32_t input)
{
    const uint32_t vDda = 330;
    const uint32_t fullScale = 4096;
    const uint32_t vRefCal = 0x0000000000000fff & (uint64_t)(ST_VREFINT_CAL);
    uint32_t vOut = (vDda * input * vRefCal) / (measures.vrefMeasured * fullScale);
    // на выходе напряжение в вольтах умноженное на 100, что бы не мучать проц
    // операциями с плавающей точкой и уложиться в пределы 32х разрядов
    return (uint32_t)vOut;
}

uint32_t getTemperature()
{
    const uint32_t vRefCal = (uint32_t)(0x0000000000000fff & (uint64_t)(ST_VREFINT_CAL));
    const int32_t avgSlope = 5336;
    const int32_t tempCal30 = 0x00000fff & (uint32_t)(ST_TSENSE_CAL1_30C);

    int32_t tempRawCal = ((uint32_t)(measures.temperature&0xfff) * vRefCal) / ((uint32_t)(measures.vrefMeasured&0xfff));
    int32_t temp = ((((int32_t)tempCal30 - tempRawCal)*1000) / avgSlope) + 30;
    if (temp < 0) return 0;
    return (uint32_t)temp;
}

int8_t getHandlePos()
{
    const int handleMin = 0;
    const int handleMax = 3400;
    int pos = ((((int)measures.handle) - handleMin) * 100) / (handleMax - handleMin);
    if( pos > 100 ) pos = 100;
    if( pos < 0 )   pos = 0;
    return (int8_t)pos;
}

int8_t getHandlePosP(uint32_t par)
{
    const int32_t handleMin = 0;
    const int32_t handleMax = 3400;
    int32_t pos = ((((int32_t)par) - handleMin) * 100) / (handleMax - handleMin);
    if( pos > 100 ) pos = 100;
    if( pos < 0 )   pos = 0;
    return (int8_t)pos;
}

uint32_t getVoltage()
{
//    const uint32_t voltageScale = 10514; это был рассчетный коэффициент
    const uint32_t voltageScale = 102;
    return adcToVoltage((uint16_t)measures.voltage) * voltageScale / 10;
}

uint32_t getAmps()
{
    const uint32_t vDda = 3300;
    const uint32_t fullScale = 4096;
    const uint32_t vRefCal = 0x0000000000000fff & (uint64_t)(ST_VREFINT_CAL);
    uint32_t vOut = (((vDda * vRefCal) / measures.vrefMeasured) * measures.current) / fullScale;

    const uint32_t ampsScale = 18; // 0,0196 ом при 5 по 0,1 параллельно
    return (vOut / ampsScale) * 100;
}
