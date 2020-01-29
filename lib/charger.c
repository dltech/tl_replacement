#include "charger.h"
#include "display.h"
#include "tl.h"
#include "time.h"


extern volatile uint32_t dispBuffer[DIGITS];
extern volatile tlParams tlPar;

enum chargeState {
    START = 0,
    CHECK,
    BULK,
    ABSORPTION,
    EQUALIZATION,
    MAINTANCE,
    ERROR
};

typedef struct {
    uint32_t minimumAmp;
    uint32_t constantAmp;
    uint32_t equalizationAmp;
    uint32_t maintanceAmp;
    uint32_t constantCurrent;
    uint32_t lowCurrent;
    uint32_t voltageDelta;
    uint32_t currentDelta;
    uint32_t wireDrop;
} chargeTable;


volatile struct chargeSettings {
    uint32_t state;
    uint32_t stabCnt;
    uint32_t nCycles;
    uint16_t totalTime;
    const uint8_t dispUpdateDiv;
    const uint32_t stabAmount;
    const uint32_t bulkTime;
    const uint32_t absorptionTime;
    const uint32_t equalizationTime;
} chSet = {CHECK, 0, 0, 0, 25, 200, 48*60, 8*60, 30};

void chargeLable(void);
void charge(chargeTable *table);

void chargeLable()
{
    enum display {
        LABEL = 0,
        VOLTAGE,
        CURRENT,
        TIME
    };
    const char lbl[ERROR + 1][4] = { {'c', 'h', 'k', '\0'},
                                     {'c', 'h', 'k', '\0'},
                                     {'1', '_', '3', '\0'},
                                     {'2', '_', '3', '\0'},
                                     {'3', '_', '3', '\0'},
                                     {' ', 'o', 'k', '\0'},
                                     {'e', 'r', 'r', '\0'} };
    static uint8_t cnt = 0;
    static uint8_t mode = LABEL;
    if(++cnt < chSet.dispUpdateDiv) {
        return;
    }
    if(++mode > TIME) {
        mode = LABEL;
    }

    if( chSet.state == ERROR ) {
        dsprintf((uint32_t*)dispBuffer, "%s", lbl[ERROR]);
        return;
    }
    if( chSet.state == START ) {
        dsprintf((uint32_t*)dispBuffer, "%s", lbl[START]);
        return;
    }
    switch( mode ) {
        case LABEL:
            dsprintf((uint32_t*)dispBuffer, "%s", lbl[chSet.state]);
            break;
        case VOLTAGE:
            dsprintf((uint32_t*)dispBuffer, "%02d%c", tlPar.meanVoltage/100, 'v');
            break;
        case CURRENT:
            dsprintf((uint32_t*)dispBuffer, "%01d.%01d%c", tlPar.meanCurrent/100, (tlPar.meanCurrent%100)/10, 'a');
            break;
        case TIME:
            dsprintf((uint32_t*)dispBuffer, "%02d%c", chSet.totalTime/60, 'h');
    }
}

void resetCharger()
{
    chSet.state = START;
}

void charge(chargeTable *table)
{
    uint32_t par = 0;
    static uint32_t parOld = 0;

    chargeLable();
    switch( chSet.state )
    {
        case START:
            tlPar.setVoltage = 0;
            tlPar.setCurrent = tlPar.minCurrent;
            ++chSet.stabCnt;
            if( (chSet.stabCnt > chSet.stabAmount) && (tlPar.duty == tlPar.minDuty) ) {
                chSet.state = CHECK;
                chSet.stabCnt = 0;
            }
            break;
        case CHECK:
            if( tlPar.voltage >= table->minimumAmp ) {
                ++chSet.stabCnt;
            } else {
                chSet.stabCnt = 0;
            }
            if( chSet.stabCnt > chSet.stabAmount ) {
                tlPar.setVoltage = table->constantAmp;uint8_t percent(void);

                tlPar.setCurrent = table->constantCurrent;
                chSet.stabCnt = 0;
                chSet.totalTime = catchTime();
                chSet.state = BULK;
            }
            break;
        case BULK:
            if( tlPar.voltage >= table->maintanceAmp ) {
                ++chSet.stabCnt;
            } else {
                chSet.stabCnt = 0;
            }
            if( chSet.stabCnt > chSet.stabAmount ) {
                chSet.stabCnt = 0;
                tlPar.setVoltage = table->constantAmp;
                chSet.totalTime += catchTime();
                chSet.state = ABSORPTION;
            }
            if( (par = elapsedTime()) > chSet.bulkTime) {
                chSet.state = ERROR;
            }
            break;
        case ABSORPTION:
            if( tlPar.current <= table->lowCurrent ) {
                ++chSet.stabCnt;
            } else {
                chSet.stabCnt = 0;
            }
            if( chSet.stabCnt > chSet.stabAmount ) {
                tlPar.setVoltage = table->maintanceAmp;
                tlPar.setCurrent = table->lowCurrent;
                chSet.stabCnt = 0;
                chSet.totalTime += catchTime();
                chSet.state = MAINTANCE;
            }
            if( (par = elapsedTime()) > chSet.absorptionTime ) {
                tlPar.setVoltage = table->equalizationAmp;
                tlPar.setCurrent = table->lowCurrent;
                chSet.stabCnt = 0;
                chSet.totalTime += catchTime();
                chSet.state = EQUALIZATION;
            }
            break;
        case EQUALIZATION:
            if( tlPar.voltage >= table->equalizationAmp ) {
                ++chSet.stabCnt;
            } else {
                chSet.stabCnt = 0;
            }
            if( chSet.stabCnt > chSet.stabAmount ) {
                tlPar.setVoltage = table->maintanceAmp;
                chSet.stabCnt = 0;
                chSet.state = MAINTANCE;
            }
            if( (par = elapsedTime()) > chSet.equalizationTime ) {
                chSet.state = CHECK;
            }
            break;
        case MAINTANCE:
            if( tlPar.voltage < (table->maintanceAmp - table->voltageDelta) ) {
                ++chSet.stabCnt;
            } else {
                chSet.stabCnt = 0;
            }
            if( chSet.stabCnt > chSet.stabAmount ) {
                chSet.stabCnt = 0;
                chSet.state = CHECK;
            }
            break;
        case ERROR:
            tlPar.setVoltage = 0;
            tlPar.setCurrent = 0;
            break;
    }
    chSet.totalTime = chSet.totalTime - parOld + par;
    parOld = par;
}

void chargeAuto()
{
    // вводим таблицу с поправкой на сопротивление проводов (при таких токах и 0,05 ома ощутимо)
    chargeTable car = { 500, 1500, 1570, 1370, 600, 100, 50, 500, 100 };
    car.constantAmp += car.wireDrop;
    car.equalizationAmp += car.wireDrop;
    car.maintanceAmp += car.wireDrop;
    charge(&car);
}

void chargeMoto()
{
    chargeTable moto = { 200,  700,  770,  670, 300, 70,  50, 500, 100 };
    moto.constantAmp += moto.wireDrop;
    moto.equalizationAmp += moto.wireDrop;
    moto.maintanceAmp += moto.wireDrop;
    charge(&moto);
}
