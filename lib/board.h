#ifndef H_BOARD
#define H_BOARD

#include "../libopencm3/include/libopencm3/stm32/gpio.h"

/*  This firmware works without any OS throw the timers interrupts. There are
    timer funcions:
    TIM1  - shift registers of the display
    TIM3  - PWM outputs of the driver
    TIM14 - driver feedback interrupt
    TIM15 - menu update interrupt
    TIM16 - cooling fan PWM
    TIM17 - buttons checks
*/

#define FAN_PORT      GPIOA
#define FAN_PIN       GPIO6

#define BUTTON_PORT        GPIOA
#define BUTTON_READ        GPIOA_IDR
#define SET_PIN            GPIO9
#define CHOOSE_PIN         GPIO10

#define DISPLAY_EN_PORT    GPIOB
#define EN_PIN             GPIO1
#define DISPLAY_PORT       GPIOA
#define NSS_NC             GPIO4
#define CLOCK_PIN          GPIO5
#define DATA_PIN           GPIO7

#define TIMEOUT_CLKS       9e6

void clkInit(void);
void fanInit(void);
void displayInit(void);
void menuInit(void);
void fanUpdate(void);

#endif
