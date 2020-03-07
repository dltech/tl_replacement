#ifndef H_TL
#define H_TL

#define TEMP_LIMIT      100
#define CURRENT_LIMIT   1000
#define VOLTAGE_LIMIT   2500

#define PWM_BORDER   TIM3_CCR1

#define TLOUT_RCC_EN  RCC_AHBENR_GPIOFEN
#define TLOUT_PORT    GPIOF
#define TL1OUT_PIN    GPIO0
#define TL2OUT_PIN    GPIO1

typedef struct {
    const uint32_t divider;
    const uint32_t maxVoltage;
    const uint32_t minVoltage;
    const uint32_t maxCurrent;
    const uint32_t minCurrent;
    const int32_t maxDuty;
    const int32_t minDuty;
    uint32_t meanVoltage;
    uint32_t meanCurrent;
    uint32_t setVoltage;
    uint32_t setCurrent;
    uint32_t voltage;
    uint32_t current;
    int32_t duty;
    uint8_t lockFlag;
} tlParams;

void tlInit(void);
void tlLock(void);
void tlUnlock(void);
void fault(void);

#endif
