#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "../libopencm3/include/libopencm3/stm32/rcc.h"
#include "../libopencm3/include/libopencm3/stm32/exti.h"
#include "../libopencm3/include/libopencm3/stm32/gpio.h"
#include "../libopencm3/include/libopencm3/stm32/timer.h"
#include "../libopencm3/include/libopencm3/cm3/nvic.h"
#include "buttons.h"
#include "menu.h"

extern volatile menuSettings menuSet;
volatile uint32_t buttons = 0xffffffff;

void buttonsInit()
{
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
    TIM17_ARR   = (uint32_t) 5;
    TIM17_DIER  = (uint32_t) TIM_DIER_UIE;
    TIM17_EGR  |= (uint32_t) TIM_EGR_UG;
    TIM17_SR = 0;
    nvic_enable_irq(NVIC_TIM17_IRQ);
    nvic_set_priority(NVIC_TIM17_IRQ, 0x40);
}

void startButtonsCheck()
{
    // when the button is pressed, off the interrupt of button
    exti_disable_request(EXTI9 | EXTI10);
    EXTI_PR = 0xffffffff;
    // check buttons
    buttons = BUTTON_READ;
    // and start three another checks throw the delays
    TIM17_SR = 0;
    TIM17_CR1 |= (uint32_t) TIM_CR1_CEN;
}

void checkButtonResetTimer()
{
    static uint8_t counter = 0;
    if( counter > 254 ) counter = 0;
    const uint8_t minimal = 3;

    TIM17_SR = 0;
    uint32_t prevButtons = buttons;
    buttons |= (uint32_t)BUTTON_READ;
    if( ((~buttons) & (CHOOSE_PIN | SET_PIN)) > 0 ) {
        ++counter;
        TIM17_CR1 |= (uint32_t) TIM_CR1_CEN;
        return;
    }

    if( (counter > minimal) && ((prevButtons & SET_PIN) == 0) ) {
        menuSet.setButFlag = 1;
    } else if( (counter > minimal) && ((prevButtons & CHOOSE_PIN) == 0) ) {
        menuSet.cvButFlag = 1;
    }

    counter = 0;
    EXTI_PR = 0xffffffff;
    exti_enable_request(EXTI9 | EXTI10);
}
