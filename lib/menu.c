#include <limits.h>
#include "../libopencm3/include/libopencm3/stm32/timer.h"
#include "menu.h"
#include "measure.h"
#include "tl.h"
#include "display.h"
#include "charger.h"



extern volatile uint32_t dispBuffer[DIGITS];
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
    CHARGER_6
};

volatile struct menuSettings{
    uint32_t state;
    uint32_t chargerDispMode;
    uint32_t meanVoltage;
    uint32_t meanCurrent;
    uint32_t handle;
    uint32_t cnt;
    const uint32_t updateFreq;
    const uint32_t cntMax;
} menuSet = {MANUAL_VOLTAGE, 0, 0, 0, 101, 0, 10, 10*2 };

enum chargerDispModeEnum {
    DISP_VOLTAGE = 1,
    DISP_CURRENT,
    DISP_TEXT
};

void checkHandle(void);
uint32_t handleToCurrent(void);
uint32_t handleToVoltage(void);


void setButton()
{
    menuSet.cnt = 0;
    switch ( menuSet.state ) {
        case MANUAL_CURRENT:
        case MANUAL_VOLTAGE:
        case MANUAL_VOLTAGE_CHANGED:
        case MANUAL_CURRENT_CHANGED:
            menuSet.state = CHARGER_12_NEWBIE;
            break;
        case CHARGER_12:
            menuSet.state = CHARGER_6_NEWBIE;
            break;
        case CHARGER_6:
            menuSet.state = MANUAL_VOLTAGE;
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
        case MANUAL_VOLTAGE_CHANGED:
            menuSet.state = MANUAL_CURRENT_NEWBIE;
            break;
        case MANUAL_CURRENT:
        case MANUAL_CURRENT_CHANGED:
            menuSet.state = MANUAL_VOLTAGE_NEWBIE;
            break;
        case CHARGER_12:
            menuSet.chargerDispMode = DISP_TEXT;
            break;
        default:
            menuSet.state = MANUAL_VOLTAGE;
    }
}

void checkHandle()
{
    uint32_t pos = getHandlePos();
    if( pos != menuSet.handle ) {
        switch ( menuSet.state ) {
            case MANUAL_VOLTAGE:
            case MANUAL_VOLTAGE_CHANGED:
                menuSet.cnt = 0;
                menuSet.state = MANUAL_VOLTAGE_CHANGED;
                break;
            case MANUAL_CURRENT:
            case MANUAL_CURRENT_CHANGED:
                menuSet.cnt = 0;
                menuSet.state = MANUAL_CURRENT_CHANGED;
                break;
        }
        menuSet.handle = pos;
    }
}

uint32_t handleToVoltage()
{
    uint32_t volt = menuSet.handle*tlPar.maxVoltage / 100;
    if( volt > tlPar.maxVoltage ) {
        volt = tlPar.maxVoltage;
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
                dsprintf((uint32_t*)dispBuffer, "vol");
            }
            if( menuSet.cnt > menuSet.cntMax ) {
                menuSet.meanVoltage = tlPar.voltage;
                menuSet.state = MANUAL_VOLTAGE;
            }
            break;
        case MANUAL_VOLTAGE:
            dsprintf((uint32_t*)dispBuffer, "%02d.%01d", tlPar.meanVoltage/100, (tlPar.meanVoltage%100)/10);
            break;
        case MANUAL_VOLTAGE_CHANGED:
            if( menuSet.cnt == 0 ) {
                tlPar.setVoltage = handleToVoltage();
                dsprintf((uint32_t*)dispBuffer, "%02d.%01d",  tlPar.setVoltage/100, (tlPar.setVoltage%100)/10);
            }
            if( menuSet.cnt > menuSet.cntMax ) {
                menuSet.cnt = 0;
                dsprintf((uint32_t*)dispBuffer, "%02d.%01d",  tlPar.voltage/100, (tlPar.voltage%100)/10);
                menuSet.state = MANUAL_VOLTAGE;
            }
            break;
        case MANUAL_CURRENT_NEWBIE:
            if( menuSet.cnt == 0 ) {
                dsprintf((uint32_t*)dispBuffer, "amp");
            }
            if( menuSet.cnt > menuSet.cntMax ) {
                menuSet.meanCurrent = tlPar.current;
                menuSet.state = MANUAL_CURRENT;
            }
            break;
        case MANUAL_CURRENT:
            dsprintf((uint32_t*)dispBuffer, "%02d.%01d", tlPar.meanCurrent/100, (tlPar.meanCurrent%100)/10);
            break;
        case MANUAL_CURRENT_CHANGED:
            if( menuSet.cnt == 0 ) {
                tlPar.setCurrent = handleToCurrent();
                dsprintf((uint32_t*)dispBuffer, "%02d.%01d", tlPar.setCurrent/100, (tlPar.setCurrent%100)/10);
            }
            if( menuSet.cnt > menuSet.cntMax ) {
                menuSet.cnt = 0;
                dsprintf((uint32_t*)dispBuffer, "%02d.%01d", tlPar.current/100, (tlPar.current%100)/10);
                menuSet.state = MANUAL_CURRENT;
            }
            break;
        case CHARGER_12_NEWBIE:
            if( menuSet.cnt == 0 ) {
                dsprintf((uint32_t*)dispBuffer, "b12");
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
                dsprintf((uint32_t*)dispBuffer, "b06");
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
    }
    ++menuSet.cnt;
    if( menuSet.cnt > INT_MAX ) {
        menuSet.cnt = menuSet.cntMax;
    }
}
