#ifndef H_TL
#define H_TL

#define PWM_BORDER   TIM3_CCR1

#define TLOUT_RCC_EN  RCC_AHBENR_GPIOFEN
#define TLOUT_PORT    GPIOF
#define TL1OUT_PIN    GPIO0
#define TL2OUT_PIN    GPIO1

typedef struct {
    const uint32_t upToDown;
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
} tlParams;

void tl_init(void);
void fault(void);

#endif
