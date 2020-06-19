#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "tl.h"
#include "measure.h"
#include "settings.h"
#include "menu.h"

#include "../libopencm3/include/libopencm3/stm32/rcc.h"

#include "../libopencm3/include/libopencm3/stm32/timer.h"


#include "display.h"
extern volatile tlParams tlPar;
extern volatile menuSettings menuSet;
extern uint32_t debugduty;



int main(void)
{
    clkInit();
    displayInit();
    fanInit();
    setInit();
    menuInit();
    tlInit();


    while(1);
/*    RCC_APB1ENR |= RCC_APB1ENR_TIM14EN;
    TIM14_CR1   = (uint32_t) TIM_CR1_CKD_CK_INT;
    TIM14_PSC   = (uint32_t) 65535;
    TIM14_ARR   = (uint32_t) 48;
    TIM14_DIER  = (uint32_t) TIM_DIER_UIE;
    TIM14_CR1  |= (uint32_t) TIM_CR1_CEN;
    TIM14_EGR  |= (uint32_t) TIM_EGR_UG;
    TIM14_SR = 0;

    while(1) {
        while((TIM14_SR & TIM_SR_UIF) == 0 );
        TIM14_SR = 0;
        debugduty = median(getHandlePos()) * 768 / 100;
        myprintf("%3d",getVoltage()/10);
    } */
}
