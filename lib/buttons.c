#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "../libopencm3/include/libopencm3/stm32/gpio.h"
#include "../libopencm3/include/libopencm3/stm32/timer.h"


volatile uint32_t buttons = 0xffffffff;
volatile uint8_t checkCnt = 0;

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
    TIM17_ARR   = (uint32_t) 3;
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
    checkCnt = 0;
    // and start three another checks throw the delays
    TIM17_SR = 0;
    TIM17_CR1 |= (uint32_t) TIM_CR1_CEN;
}

void checkButtonResetTimer()
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