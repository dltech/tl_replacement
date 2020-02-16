#include <limits.h>
#include <math.h>
#include "../libopencm3/include/libopencm3/stm32/timer.h"
#include "menu.h"
#include "measure.h"
#include "tl.h"
#include "display.h"
#include "charger.h"


extern volatile tlParams tlPar;

enum menuState {
    MANUAL_VOLTAGE_NEWBIE = 1,
    MANUAL_VOLTAGE,
    MANUAL_VOLTAGE_CHANGED,
    MANUAL_CURRENT_NEWBIE,
    MANUAL_CURRENT,
    MANUAL_CURRENT_CHANGED,
    CHARGER_12_NEWBIE,
    CHARGER_12,
    CHARGER_6_NEWBIE,
    CHARGER_6,
    OFF
};

volatile struct menuSettings{
    uint32_t state;
    uint32_t meanVoltage;
    uint32_t meanCurrent;
    uint32_t handle;
    uint32_t cnt;
    const uint32_t updateFreq;
    const uint32_t cntMax;
} menuSet = {MANUAL_VOLTAGE, 0, 0, 101, 0, 10, 10*2 };


void checkHandle(void);
uint32_t handleToCurrent(void);
uint32_t handleToVoltage(void);


void setButton()
{
    menuSet.cnt = 0;
    switch ( menuSet.state ) {
        case MANUAL_VOLTAGE:
        case MANUAL_VOLTAGE_CHANGED:
        case MANUAL_VOLTAGE_NEWBIE:
        case MANUAL_CURRENT:
        case MANUAL_CURRENT_CHANGED:
        case MANUAL_CURRENT_NEWBIE:
            menuSet.state = CHARGER_12_NEWBIE;
            break;
        case CHARGER_12_NEWBIE:
        case CHARGER_12:
            menuSet.state = CHARGER_6_NEWBIE;
            break;
        case CHARGER_6_NEWBIE:
        case CHARGER_6:
            menuSet.state = MANUAL_VOLTAGE_NEWBIE;
            break;
        case OFF:
            break;
        default:
            menuSet.state = MANUAL_VOLTAGE;
    }
}

void currentVoltageButton()
{
    menuSet.cnt = 0;
    switch ( menuSet.state ) {
        case MANUAL_VOLTAGE:
        case MANUAL_VOLTAGE_NEWBIE:
        case MANUAL_VOLTAGE_CHANGED:
            menuSet.state = MANUAL_CURRENT_NEWBIE;
            break;
        case MANUAL_CURRENT:
        case MANUAL_CURRENT_NEWBIE:
        case MANUAL_CURRENT_CHANGED:
            menuSet.state = MANUAL_VOLTAGE_NEWBIE;
            break;
        case CHARGER_6_NEWBIE:
        case CHARGER_12_NEWBIE:
            break;
        case CHARGER_6:
        case CHARGER_12:
            chargeLable(1);
            break;
        case OFF:
            break;
        default:
            menuSet.state = MANUAL_VOLTAGE;
    }
}

void checkHandle()
{
    uint32_t pos = 100 - getHandlePos();
    if( fabs(pos - menuSet.handle) < HANDLE_DELTA ) {
        return;
    }

    switch ( menuSet.state ) {
        case MANUAL_VOLTAGE_NEWBIE:
            if(pos < HANDLE_DELTA) {
                tlPar.setVoltage = 0;
                menuSet.state = OFF;
            }
            break;
        case MANUAL_VOLTAGE:
        case MANUAL_VOLTAGE_CHANGED:
            menuSet.cnt = 0;
            if(pos < HANDLE_DELTA) {
                tlPar.setVoltage = 0;
                menuSet.state = OFF;
            } else {
                menuSet.state = MANUAL_VOLTAGE_CHANGED;
            }
            break;
        case MANUAL_CURRENT_NEWBIE:
            if(pos < HANDLE_DELTA) {
                tlPar.setVoltage = 0;
                tlPar.setCurrent = 0;
                menuSet.state = OFF;
            }
            break;
        case MANUAL_CURRENT:
        case MANUAL_CURRENT_CHANGED:
            menuSet.cnt = 0;
            if(pos < HANDLE_DELTA) {
                tlPar.setVoltage = 0;
                tlPar.setCurrent = 0;
                menuSet.state = OFF;
            } else {
                menuSet.state = MANUAL_CURRENT_CHANGED;
            }
            break;
        case CHARGER_6_NEWBIE:
        case CHARGER_12_NEWBIE:
        case CHARGER_6:
        case CHARGER_12:
            if(pos < HANDLE_DELTA) {
                tlPar.setVoltage = 0;
                tlPar.setCurrent = 0;
                menuSet.state = OFF;
            }
            break;
        case OFF:
            if(pos >= HANDLE_DELTA) {
                menuSet.state = MANUAL_VOLTAGE_NEWBIE;
            }
            break;
    }
    menuSet.handle = pos;
}

uint32_t handleToVoltage()
{
    uint32_t volt = menuSet.handle*tlPar.maxVoltage / 100;
    if( volt > tlPar.maxVoltage ) {
        volt = tlPar.maxVoltage;
    } else if( volt < (tlPar.minVoltage / 2) ) {
        volt = 0;
    } else if( volt < tlPar.minVoltage ) {
        volt = tlPar.minVoltage;
    }
    return volt;
}

uint32_t handleToCurrent()
{
    uint32_t curr = menuSet.handle*tlPar.maxCurrent / 100;
    if( curr > tlPar.maxCurrent ) {
        curr = tlPar.maxCurrent;
    } else if( curr < tlPar.minCurrent ) {
        curr = tlPar.minCurrent;
    }
    return curr;
}

void menu()
{
    checkHandle();
    switch( menuSet.state )
    {
        case MANUAL_VOLTAGE_NEWBIE:
            if( menuSet.cnt == 0 ) {
                myprintf("vol");
            }
            if( menuSet.cnt > menuSet.cntMax ) {
                menuSet.meanVoltage = tlPar.voltage;
                menuSet.state = MANUAL_VOLTAGE;
            }
            break;
        case MANUAL_VOLTAGE:
            myprintf("%02d.%01d", tlPar.meanVoltage/100, (tlPar.meanVoltage%100)/10);
            break;
        case MANUAL_VOLTAGE_CHANGED:
            if( menuSet.cnt == 0 ) {
                tlPar.setVoltage = handleToVoltage();
                myprintf("%02d.%01d",  tlPar.setVoltage/100, (tlPar.setVoltage%100)/10);
            }
            if( menuSet.cnt > menuSet.cntMax ) {
                menuSet.cnt = 0;
                myprintf("%02d.%01d",  tlPar.voltage/100, (tlPar.voltage%100)/10);
                menuSet.state = MANUAL_VOLTAGE;
            }
            break;
        case MANUAL_CURRENT_NEWBIE:
            if( menuSet.cnt == 0 ) {
                myprintf("amp");
            }
            if( menuSet.cnt > menuSet.cntMax ) {
                menuSet.meanCurrent = tlPar.current;
                menuSet.state = MANUAL_CURRENT;
            }
            break;
        case MANUAL_CURRENT:
            myprintf("%02d.%01d", tlPar.meanCurrent/100, (tlPar.meanCurrent%100)/10);
            break;
        case MANUAL_CURRENT_CHANGED:
            if( menuSet.cnt == 0 ) {
                tlPar.setCurrent = handleToCurrent();
                myprintf("%02d.%01d", tlPar.setCurrent/100, (tlPar.setCurrent%100)/10);
            }
            if( menuSet.cnt > menuSet.cntMax ) {
                menuSet.cnt = 0;
                myprintf("%02d.%01d", tlPar.current/100, (tlPar.current%100)/10);
                menuSet.state = MANUAL_CURRENT;
            }
            break;
        case CHARGER_12_NEWBIE:
            if( menuSet.cnt == 0 ) {
                myprintf("b12");
            }
            if( menuSet.cnt > menuSet.cntMax ) {
                resetCharger();
                menuSet.cnt = 0;
                menuSet.state = CHARGER_12;
            }
            break;
        case CHARGER_12:
            chargeAuto();
            break;
        case CHARGER_6_NEWBIE:
            if( menuSet.cnt == 0 ) {
                myprintf("b06");
            }
            if( menuSet.cnt > menuSet.cntMax ) {
                menuSet.cnt = 0;
                resetCharger();
                menuSet.state = CHARGER_6;
            }
            break;
        case CHARGER_6:
            chargeMoto();
            break;
        case OFF:
            if( tlPar.meanVoltage > tlPar.minVoltage/10 ) {
                myprintf("%02d.%01d", tlPar.meanVoltage/100, (tlPar.meanVoltage%100)/10);
            } else {
                myprintf("off");
            }
            break;
    }
    ++menuSet.cnt;
    if( menuSet.cnt > INT_MAX ) {
        menuSet.cnt = menuSet.cntMax;
    }
}

void saveSettings()
{
    
}

void loadSettings();
