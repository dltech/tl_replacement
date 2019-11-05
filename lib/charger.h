#ifndef H_CHARGE
#define H_CHARGE

#include <inttypes.h>

uint32_t catchTime(void);
uint32_t elapsedTime(void);
uint32_t minutesFromMe(uint32_t rtcDrr, uint32_t rtcTrr);
void chargeLable(uint32_t mode);
void resetCharger(void);
void chargeAuto(void);
void chargeMoto(void);

#endif
