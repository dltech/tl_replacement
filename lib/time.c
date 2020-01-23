#include "time.h"

volatile struct chargeSettings {
    uint32_t tr;
    uint32_t dr;
} time = {0,0};


void rtcInit()
{
    // спиздил с инета, сам не вникал
    RCC_APB1ENR |= (uint32_t)RCC_APB1ENR_PWREN;
    pwr_disable_backup_domain_write_protect();
    rcc_set_rtc_clock_source(RCC_LSI);
    rcc_enable_rtc_clock();
    // тактирование от встроенного генератора 40 кГц
    rtc_unlock();
    rtc_set_prescaler(0x137, 0x7f);
    RTC_ISR |= (uint32_t)RTC_ISR_INIT;
    uint32_t timeout = 9e8;
    while( ((RTC_ISR & RTC_ISR_INITF) == 0) && (--timeout > 0) );
    // полночь, 1 января 2000
    uint32_t dr = 0;
    dr |= 0 << RTC_DR_YT_SHIFT;
    dr |= 0 << RTC_DR_YU_SHIFT;
    dr |= 6 << RTC_DR_WDU_SHIFT;
    dr |= 0 << RTC_DR_MT_SHIFT;
    dr |= 1 << RTC_DR_MU_SHIFT;
    dr |= 0 << RTC_DR_DT_SHIFT;
    dr |= 1 << RTC_DR_DU_SHIFT;
    RTC_TR = 0;
    RTC_DR = dr;
    RTC_ISR &= ~(RTC_ISR_INIT);
    rtc_lock();
}

uint32_t catchTime()
{
    uint32_t elapsed = elapsedTime();
    time.dr = RTC_DR;
    time.tr = RTC_TR;
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
    return minutesFromMe(RTC_DR, RTC_TR) - minutesFromMe(time.dr, time.tr);
}
