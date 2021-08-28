#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "tl.h"
#include "measure.h"
#include "settings.h"
#include "menu.h"
#include "display.h"




int main(void)
{
    // RCC_AHBENR |= TLOUT_RCC_EN;
    // gpio_set(TLOUT_PORT, TL1OUT_PIN | TL2OUT_PIN);
    // gpio_mode_setup(TLOUT_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, TL1OUT_PIN | TL2OUT_PIN);
    // gpio_set_output_options(TLOUT_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_100MHZ, TL1OUT_PIN | TL2OUT_PIN);

    clkInit();
    displayInit();
    fanInit();
    setInit();
    menuInit();
    tlInit();

    while(1);
}
