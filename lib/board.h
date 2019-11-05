#ifndef H_BOARD
#define H_BOARD

#include "../libopencm3/include/libopencm3/stm32/gpio.h"

/*  хоть не объявлено макросами, но напишу что куда
    TIM1  - на этом таймере работает дисплей
    TIM3  - по нему работают выходы ШИМ
    TIM14 - по этому таймеру отрабатывает обратная связь ШИМ
    TIM15 - отрисовка меню
    TIM16 - на этом таймере работает ШИМ вентилятора
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

void clkInit(void);
void fanInit(void);
void displayInit(void);
void menuInit(void);
void fanUpdate(void);

#endif
