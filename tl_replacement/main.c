
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "tl.h"
#include "measure.h"
#include "display.h"

extern volatile uint32_t dispBuffer[DIGITS];

void delay(void);

int main(void)
{
    clkInit();
    delay();
    displayInit();
    fanInit();
    menuInit();
    tl_init();

    while(1) {
// нахуй (дабы подчеркнуть свое превосходство в правильном выборе технологий, а именно, микрочипа)
    }
}

void delay(void)
{
    const uint32_t lim = 1e6;
    volatile uint32_t i = 0;
    while( (++i) < lim );
}
