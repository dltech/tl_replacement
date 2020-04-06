#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "tl.h"
#include "measure.h"
#include "settings.h"
#include "menu.h"


#include "display.h"
extern volatile tlParams tlPar;
extern volatile menuSettings menuSet;


void delay(void);


int main(void)
{
    clkInit();
    delay();
    tlInit();
    displayInit();
    fanInit();
    setInit();
    menuInit();
    while(1);
}



void delay(void)
{
    const uint32_t lim = 1e6;
    volatile uint32_t i = 0;
    while( (++i) < lim );
}
