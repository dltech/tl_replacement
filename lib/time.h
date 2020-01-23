#ifndef H_TIME
#define H_TIME

#include <inttypes.h>

void rtcInit(void);
uint32_t catchTime(void);
uint32_t elapsedTime(void);
uint32_t minutesFromMe(uint32_t rtcDrr, uint32_t rtcTrr);

#endif
