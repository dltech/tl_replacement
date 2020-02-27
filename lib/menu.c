#include <limits.h>
#include <math.h>
#include <inttypes.h>
#include "menu.h"
#include "measure.h"
#include "tl.h"
#include "display.h"
#include "charger.h"
#include "settings.h"

extern volatile tlParams tlPar;
volatile menuSettings menuSet = {OFF, 101, 0, 0, 0, 0, 0, 0, 0, 10, 10*2 };
extern volatile adcDma measures;


void checkHandle(void);
uint32_t handleToCurrent(void);
uint32_t handleToVoltage(void);
void menuCounter(void);
void changeState(uint8_t st);


void menuCounter()
{
    menuSet.newFlag = 0;
    if( menuSet.cnt > INT_MAX ) {
        menuSet.cnt = 1;
    } else if( menuSet.cnt > menuSet.changeTime ) {
        menuSet.ovrFlag = 1;
    } else if( menuSet.cnt == 0 ) {
        menuSet.newFlag = 1;
        menuSet.ovrFlag = 0;
    }
    ++menuSet.cnt;
}

void changeState(uint8_t st)
{
    menuSet.cnt = 0;
    menuSet.handleFlag = 0;
    menuSet.setButFlag = 0;
    menuSet.cvButFlag = 0;
    menuSet.offFlag = 0;
    menuSet.state = st;
}


void checkHandle()
{
    int8_t pos = 100 - getHandlePosP(measures.meanPar);
    if( pos < HANDLE_DELTA ) {
        menuSet.offFlag = 1;
    } else {
        menuSet.offFlag = 0;
    }
    if( pos != menuSet.handle ) {
        menuSet.handleFlag = 1;
        menuSet.handle = pos;
    } else {
        menuSet.handleFlag = 0;
    }
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
    // запускается после проверок до аутомата (чтобы правильно проставить флаги)
    menuCounter();
    switch( menuSet.state )
    {
        case MANUAL_VOLTAGE:
            if( menuSet.newFlag ) {
                myprintf("vol");
                saveSettings();
            }
            if( menuSet.ovrFlag ) {
                myprintf("%02d.%01d", tlPar.meanVoltage/100, (tlPar.meanVoltage%100)/10);
            }
            if( menuSet.offFlag ) {
                changeState(OFF);
            } else if( menuSet.handleFlag ) {
                changeState(MANUAL_VOLTAGE_CHANGED);
            } else if( menuSet.setButFlag ) {
                changeState(CHARGER_12);
            } else if( menuSet.cvButFlag ) {
                changeState(MANUAL_CURRENT);
            }
            break;
        case MANUAL_VOLTAGE_CHANGED:
            if( menuSet.newFlag ) {
                tlPar.setVoltage = handleToVoltage();
                myprintf("%02d.%01d", tlPar.setVoltage/100, (tlPar.setVoltage%100)/10);
            }
            if( menuSet.handleFlag ) {
                changeState(MANUAL_VOLTAGE_CHANGED);
            } else if( menuSet.ovrFlag ) {
                changeState(MANUAL_VOLTAGE);
                menuSet.cnt = menuSet.changeTime + 1;
            }
            break;
        case MANUAL_CURRENT:
            if( menuSet.newFlag ) {
                myprintf("cur");
                saveSettings();
            }
            if( menuSet.ovrFlag ) {
                myprintf("%02d.%01d", tlPar.meanCurrent/100, (tlPar.meanCurrent%100)/10);
            }
            if( menuSet.offFlag ) {
                changeState(OFF);
            } else if( menuSet.handleFlag ) {
                changeState(MANUAL_CURRENT_CHANGED);
            } else if( menuSet.setButFlag ) {
                changeState(CHARGER_12);
            } else if( menuSet.cvButFlag ) {
                changeState(MANUAL_VOLTAGE);
            }
            break;
        case MANUAL_CURRENT_CHANGED:
            if( menuSet.newFlag ) {
                tlPar.setCurrent = handleToCurrent();
                myprintf("%02d.%01d", tlPar.setCurrent/100, (tlPar.setCurrent%100)/10);
            }
            if( menuSet.handleFlag ) {
                changeState(MANUAL_CURRENT_CHANGED);
            } else if( menuSet.ovrFlag ) {
                changeState(MANUAL_CURRENT);
                menuSet.cnt = menuSet.changeTime + 1;
            }
            break;
        case CHARGER_12:
            if( menuSet.newFlag ) {
                myprintf("b12");
                resetCharger();
                saveSettings();
            }
            if( menuSet.ovrFlag ) {
                chargeLable(0);
                chargeAuto();
            }
            if( menuSet.offFlag ) {
                changeState(OFF);
            } else if( menuSet.setButFlag ) {
                changeState(CHARGER_6);
            } else if( menuSet.cvButFlag ) {
                chargeLable(1);
            } else {
                chargeLable(0);
            }
            break;
        case CHARGER_6:
            if( menuSet.newFlag ) {
                myprintf("b06");
                resetCharger();
                saveSettings();
            }
            if( menuSet.ovrFlag ) {
                chargeMoto();
            }
            if( menuSet.offFlag ) {
                changeState(OFF);
            } else if( menuSet.setButFlag ) {
                changeState(MANUAL_VOLTAGE);
            } else if( menuSet.cvButFlag ) {
                chargeLable(1);
            } else {
                chargeLable(0);
            }
            break;
        case OFF:
            if( tlPar.meanVoltage > tlPar.minVoltage/10 ) {
                myprintf("%02d.%01d", tlPar.meanVoltage/100, (tlPar.meanVoltage%100)/10);
            } else {
                myprintf("off");
            }
            if( menuSet.offFlag == 0 ) {
                changeState(loadSettings());
            }
            break;
        default:
            fault();
            break;
    }
}
