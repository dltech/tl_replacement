#ifndef H_MEASURE
#define H_MEASURE
#include "../libopencm3/include/libopencm3/stm32/adc.h"

#define TEMP_LIMIT      100
#define CURRENT_LIMIT   1000
#define VOLTAGE_LIMIT   2500

#define CURRENT_CH         2
#define VOLTAGE_CH         3
#define HANDLE_CH          0
#define TEMP_CH            ADC_CHANNEL_TEMP
#define ADC_NUMBER         4
#define ADC_CHANNELS       (1 << TEMP_CH) | (1 << VOLTAGE_CH) | (1 << CURRENT_CH) | (1 << HANDLE_CH)

#define MEASURE_PORT  GPIOA
#define VOLTAGE_PIN   GPIO3
#define CURRENT_PIN   GPIO2
#define HANDLE_PIN    GPIO0
#define MEASURE_PINS  VOLTAGE_PIN | CURRENT_PIN | HANDLE_PIN

typedef struct {
    uint32_t handle;
    uint32_t current;
    uint32_t voltage;
    uint32_t temperature;
    uint32_t vrefMeasured;
} adcDma;

void measureInit(void);

int getTemperature(void);
int8_t getHandlePos(void);
uint32_t getVoltage(void);
uint32_t getAmps(void);


#endif
