#include "charger.h"
#include "display.h"
#include "tl.h"
#include "../libopencm3/include/libopencm3/stm32/rtc.h"


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
} chargeTable;

volatile struct chargeSettings {
    uint32_t state;
    uint32_t stabCnt;
    uint32_t rtcTr;
    uint32_t rtcDr;
    uint32_t nCycles;
    uint16_t totalTime;
    const uint32_t stabAmount;
    const uint32_t bulkTime;
    const uint32_t absorptionTime;
    const uint32_t equalizationTime;
} chSet = {CHECK, 0, 0, 0, 0, 0, 200, 48*60, 8*60, 30};

void charge(chargeTable *table);

uint32_t catchTime()
{
    uint32_t elapsed = elapsedTime();
    chSet.rtcDr = RTC_DR;
    chSet.rtcTr = RTC_TR;
    return elapsed;
}

uint32_t minutesFromMe(uint32_t rtcDrr, uint32_t rtcTrr)
{
    const uint32_t hour = 60;
    const uint32_t day  = hour*24;
    const uint32_t year = day*365;
    uint32_t minutes = ((rtcDrr >> RTC_DR_YT_SHIFT) & RTC_DR_YT_MASK) * year*10;
    minutes += ((rtcDrr >> RTC_DR_YU_SHIFT) & RTC_DR_YU_MASK) * year;
    // учитываем дни за все високосные года
    minutes += (minutes/year/4)*day;
    uint32_t mounth = ((rtcDrr >> RTC_DR_MT_SHIFT) & RTC_DR_MT_MASK)*10 + \
                      ((rtcDrr >> RTC_DR_MU_SHIFT) & RTC_DR_MU_MASK) - 1;
    switch (mounth) {
        case 11:
            minutes += 31*day;
        case 10:
            minutes += 30*day;
        case 9:
            minutes += 31*day;
        case 8:
            minutes += 30*day;
        case 7:
            minutes += 31*day;
        case 6:
            minutes += 30*day;
        case 5:
            minutes += 31*day;
        case 4:
            minutes += 30*day;
        case 3:
            minutes += 31*day;
        case 2:
            minutes += 28*day;
        case 1:
            minutes += 31*day;
            break;
    }
    minutes +=  ((rtcDrr >> RTC_DR_DT_SHIFT) & RTC_DR_DT_MASK)      * day*10;
    minutes += (((rtcDrr >> RTC_DR_DU_SHIFT) & RTC_DR_DU_MASK) - 1) * day;
    minutes += ((rtcTrr >> RTC_TR_HT_SHIFT) & RTC_TR_HT_MASK) * hour*10;
    minutes += ((rtcTrr >> RTC_TR_HU_SHIFT) & RTC_TR_HU_MASK) * hour;
    minutes += ((rtcTrr >> RTC_TR_MNT_SHIFT) & RTC_TR_MNT_MASK) * 10;
    minutes += ((rtcTrr >> RTC_TR_MNU_SHIFT) & RTC_TR_MNU_MASK);
    return minutes;
}

uint32_t elapsedTime()
{
    return minutesFromMe(RTC_DR, RTC_TR) - minutesFromMe(chSet.rtcDr, chSet.rtcTr);
}

void chargeLable(uint32_t mode)
{
    const char lbl[ERROR + 1][4] = { {'c', 'h', 'k', '\0'},
                                     {'c', 'h', 'k', '\0'},
                                     {'s', 't', '1', '\0'},
                                     {'s', 't', '2', '\0'},
                                     {'s', 't', '3', '\0'},
                                     {' ', 'o', 'k', '\0'},
                                     {'e', 'r', 'r', '\0'} };
    if( chSet.state == ERROR ) {
        dsprintf((uint32_t*)dispBuffer, "%s", lbl[ERROR]);
        return;
    }
    if( chSet.state == START ) {
        dsprintf((uint32_t*)dispBuffer, "%s", lbl[START]);
        return;
    }
    switch( mode ) {
        case 0:
            dsprintf((uint32_t*)dispBuffer, "%s", lbl[chSet.state]);
            break;
        case 1:
            dsprintf((uint32_t*)dispBuffer, "%02d%c", tlPar.meanVoltage/100, 'v');
            break;
        case 2:
            dsprintf((uint32_t*)dispBuffer, "%01d.%01d%c", tlPar.meanCurrent/100, (tlPar.meanCurrent%100)/10, 'a');
            break;
        case 3:
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

    switch( chSet.state )
    {
        case START:
            tlPar.setVoltage = 0;
            tlPar.setCurrent = tlPar.minCurrent;
            ++chSet.stabCnt;
            if( (chSet.stabCnt > chSet.stabAmount) && (tlPar.duty == tlPar.minDuty) ) {
                chSet.state = CHECK;
            }
            break;
        case CHECK:
            if( tlPar.voltage >= table->minimumAmp ) {
                ++chSet.stabCnt;
            } else {
                chSet.stabCnt = 0;
            }
            if( chSet.stabCnt > chSet.stabAmount ) {
                tlPar.setVoltage = table->constantAmp;
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
    chargeTable car = { 500, 1500+100, 1570+100, 1370+100, 600, 100, 50, 500 };
    charge(&car);
}

void chargeMoto()
{
    chargeTable moto = { 200,  700,  770,  670, 300, 70,  50, 500 };
    charge(&moto);
}
