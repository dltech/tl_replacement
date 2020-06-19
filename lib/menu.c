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

uint32_t handleToCurrent(void);
uint32_t handleToVoltage(void);
void menuCounter(void);
void changeState(uint8_t st);


uint32_t median(uint32_t in)
{
    #define size 15
    static uint32_t wind[size] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    for(int8_t i=size-1 ; i>=0 ; --i)
    {
        if( (in > wind[i]) ) {
            for(uint8_t j=0 ; j<i ; ++j) {
                wind[j] = wind[j+1];
            }
            wind[i] = in;
            break;
        } else if(i == 0) {
            for(uint8_t j=(size-1) ; j>0 ; --j) {
                wind[j] = wind[j-1];
            }
            wind[0] = in;
        }
    }
    return wind[size/2];
}

void menuCounter()
{
    menuSet.newFlag = 0;
    menuSet.ovrFlag = 0;
    if( menuSet.cnt > INT_MAX ) {
        menuSet.cnt = 1;
        menuSet.ovrFlag = 1;
    } else if( menuSet.cnt > menuSet.changeTime ) {
        menuSet.ovrFlag = 1;
    } else if( menuSet.cnt == 0 ) {
        menuSet.newFlag = 1;
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
    menuSet.newFlag = 0;
    menuSet.ovrFlag = 0;
    menuSet.state = st;
}


void checkHandle()
{
    uint8_t pos = (uint8_t)(median(100 - getHandlePosP(measures.handle)));
    menuSet.handleFlag = 0;
    menuSet.offFlag = 0;
    if( pos < HANDLE_DELTA ) {
        menuSet.offFlag = 1;
        menuSet.handle = 0;
        return;
    }
    if( pos != menuSet.handle ) {
        menuSet.handleFlag = 1;
        menuSet.handle = pos;
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

uint32_t menuc = 0;
void menu()
{
    ++menuc;
    checkHandle();
    // запускается после проверок до аутомата (чтобы правильно проставить флаги)
    menuCounter();
    switch( menuSet.state )
    {
        case MANUAL_VOLTAGE:
            if( menuSet.offFlag ) {
                changeState(OFF);
                break;
            }
            if( menuSet.handleFlag ) {
                changeState(MANUAL_VOLTAGE_CHANGED);
                break;
            }
            if( menuSet.setButFlag ) {
                changeState(CHARGER_12);
                break;
            }
            if( menuSet.cvButFlag ) {
                changeState(MANUAL_CURRENT);
                break;
            }
            if( menuSet.ovrFlag ) {
                myprintf("%02d.%01d", tlPar.meanVoltage/100, (tlPar.meanVoltage%100)/10);
                break;
            }
            if( menuSet.newFlag ) {
                myprintf("vol");
                if( isEqual() ) break;
                tlLock();
                saveSettings();
                break;
            }
            break;
        case MANUAL_VOLTAGE_CHANGED:
            if( menuSet.newFlag ) {
                tlPar.setVoltage = handleToVoltage();
                myprintf("%02d.%01d", tlPar.setVoltage/100, (tlPar.setVoltage%100)/10);
                break;
            }
            if( menuSet.handleFlag ) {
                changeState(MANUAL_VOLTAGE_CHANGED);
                break;
            }
            if( menuSet.ovrFlag ) {
                changeState(MANUAL_VOLTAGE);
                menuSet.cnt = menuSet.changeTime + 1;
                break;
            }
            break;
        case MANUAL_CURRENT:
            if( menuSet.offFlag ) {
                changeState(OFF);
                break;
            }
            if( menuSet.handleFlag ) {
                changeState(MANUAL_CURRENT_CHANGED);
                break;
            }
            if( menuSet.setButFlag ) {
                changeState(CHARGER_12);
                break;
            }
            if( menuSet.cvButFlag ) {
                changeState(MANUAL_VOLTAGE);
                break;
            }
            if( menuSet.ovrFlag ) {
                myprintf("%02d.%01d", tlPar.meanCurrent/100, (tlPar.meanCurrent%100)/10);
                break;
            }
            if( menuSet.newFlag ) {
                myprintf("cur");
                if( isEqual() ) break;
                tlLock();
                saveSettings();
                break;
            }
            break;
        case MANUAL_CURRENT_CHANGED:
            if( menuSet.newFlag ) {
                tlPar.setCurrent = handleToCurrent();
                myprintf("%02d.%01d", tlPar.setCurrent/100, (tlPar.setCurrent%100)/10);
                break;
            }
            if( menuSet.handleFlag ) {
                changeState(MANUAL_CURRENT_CHANGED);
                break;
            }
            if( menuSet.ovrFlag ) {
                changeState(MANUAL_CURRENT);
                menuSet.cnt = menuSet.changeTime + 1;
            }
            break;
        case CHARGER_12:
            if( menuSet.offFlag ) {
                changeState(OFF);
                break;
            }
            if( menuSet.setButFlag ) {
                changeState(CHARGER_6);
                break;
            }
            if( menuSet.cvButFlag ) {
                chargeLable(1);
                break;
            }
            if( menuSet.ovrFlag ) {
                chargeLable(0);
                chargeAuto();
                break;
            }
            if( menuSet.newFlag ) {
                myprintf("b12");
                resetCharger();
                if( isEqual() ) break;
                tlLock();
                saveSettings();
                break;
            }
            break;
        case CHARGER_6:
            if( menuSet.offFlag ) {
                changeState(OFF);
                break;
            }
            if( menuSet.setButFlag ) {
                changeState(MANUAL_VOLTAGE);
                break;
            }
            if( menuSet.cvButFlag ) {
                chargeLable(1);
                break;
            }
            if( menuSet.ovrFlag ) {
                chargeMoto();
                chargeLable(0);
                break;
            }
            if( menuSet.newFlag ) {
                myprintf("b06");
                resetCharger();
                if( isEqual() ) break;
                tlLock();
                saveSettings();
                break;
            }
            break;
        case OFF:
            if( menuSet.offFlag == 0 ) {
                changeState(loadSettings());
                break;
            }
            if( menuSet.newFlag ) {
                tlPar.setVoltage = 0;
                tlPar.setCurrent = 0;
                setDuty(0);
            }
            if( tlPar.meanVoltage > tlPar.minVoltage/10 ) {
                myprintf("%02d.%01d", tlPar.meanVoltage/100, (tlPar.meanVoltage%100)/10);
            } else {
                myprintf("off");
            }
            break;
        default:
            fault();
            break;
    }
    tlUnlock();
}
