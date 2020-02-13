#ifndef H_DISPLAY
#define H_DISPLAY

#include <stdint.h>

#define SEGA  (1 << 3)
#define SEGB  (1 << 15)
#define SEGC  (1 << 9)
#define SEGD  (1 << 6)
#define SEGE  (1 << 4)
#define SEGF  (1 << 12)
#define SEGG  (1 << 11)
#define SEGDP (1 << 10)

#define BYTE0 (1 << 2)
#define BYTE1 (1 << 13)
#define BYTE2 (1 << 14)
#define MASK  (SEGA | SEGB | SEGC | SEGD | SEGE | SEGF | SEGG | SEGDP)

#define DIGITS 3

void myprintf(char *format, ... );

#endif
