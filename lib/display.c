#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "display.h"


volatile uint32_t dispBuffer[DIGITS] = {0, 0, 0};

uint32_t alphabet(char s);
void nextSymbol(uint32_t *buffer, uint8_t *n);

// свой спринтф, символы по 32 разряда для совместимости с интерфейсом
void dsprintf(uint32_t *output, char *format, ... )
{
    char buffer[DIGITS*4];
    va_list args;
    va_start (args, format);
    vsprintf (buffer, format, args);
    va_end (args);

    // проверонька
    if(strlen(buffer) > DIGITS*2)
        return;
    // Перевод в кодировку семисегментника, учитывается то условие, что точка
    // и символ на одном и том же знакоместе, а не отдельно.
    uint8_t outCnt = 0;
    for( uint8_t i = 0 ; i < strlen(buffer) ; ++i )
    {
        if(   (buffer[i] != '.')   && (buffer[i] != ',') && \
            ( (buffer[i+1] == '.') || (buffer[i+1] == ',') ) ) {
            output[outCnt] = MASK & (~(alphabet(buffer[i++]) | SEGDP));
            nextSymbol(output, &outCnt);
        } else {
            output[outCnt++] = MASK & (~(alphabet(buffer[i])));
            nextSymbol(output, &outCnt);
        }
    }
}


void nextSymbol(uint32_t *buffer, uint8_t *n)
{
    switch (*n)
    {
        case 0:
            buffer[0] |= (uint32_t) BYTE0;
            (*n)++;
            break;
        case 1:
            buffer[1] |= (uint32_t) BYTE1;
            (*n)++;
            break;
        case 2:
            buffer[2] |= (uint32_t) BYTE2;
            (*n)++;
            break;
    }
}

// латинский алфавит и цифры
uint32_t alphabet(char s)
{
    switch (s)
    {
        case '.':
        case ',':
            return SEGDP;
            break;
        case '=':
            return SEGD + SEGD;
            break;
        case '-':
            return SEGG;
            break;
        case '_':
            return SEGD;
            break;
        case '"':
            return SEGB + SEGF;
            break;
        case '\'':
            return SEGF;
            break;
        case ']':
            return SEGA + SEGB + SEGC + SEGD;
            break;
        case '2':
            return SEGA + SEGB + SEGD + SEGE + SEGG;
            break;
        case '3':
            return SEGA + SEGB + SEGC + SEGD + SEGG;
            break;
        case '4':
            return SEGB + SEGC + SEGG + SEGF;
            break;
        case '5':
            return SEGA + SEGC + SEGD + SEGF + SEGG;
            break;
        case '6':
            return SEGA + SEGC + SEGD + SEGE + SEGF + SEGG;
            break;
        case '7':
            return SEGA + SEGB + SEGC;
            break;
        case '8':
            return SEGA + SEGB + SEGC + SEGD + SEGE + SEGF + SEGG;
            break;
        case '9':
            return SEGA + SEGB + SEGC + SEGD + SEGF + SEGG;
            break;
        case 'A':
        case 'a':
            return SEGA + SEGB + SEGC + SEGE + SEGF + SEGG;
            break;
        case 'B':
        case 'b':
            return SEGC + SEGD + SEGE + SEGF + SEGG;
            break;
        case '[' :
        case 'C' :
        case 'c' :
            return SEGA + SEGD + SEGE + SEGF;
            break;
        case 'D' :
        case 'd' :
            return SEGB + SEGC + SEGD + SEGE + SEGG;
            break;
        case 'E' :
        case 'e' :
            return SEGA + SEGD + SEGE + SEGF + SEGG;
            break;
        case 'F' :
        case 'f' :
            return SEGA + SEGE + SEGF + SEGG;
            break;
        case 'G' :
        case 'g' :
            return SEGA + SEGC + SEGD + SEGE + SEGF;
            break;
        case 'H' :
        case 'h' :
        case 'x' :
        case 'X' :
            return SEGB + SEGC + SEGE + SEGF + SEGG;
            break;
        case 'I' :
        case 'i' :
        case '1' :
            return SEGB + SEGC;
            break;
        case 'J' :
        case 'j' :
            return SEGB + SEGC + SEGD;
            break;
        case 'K' :
        case 'k' :
            return SEGA + SEGC + SEGE + SEGF + SEGG;
            break;
        case 'L':
        case 'l':
            return SEGD + SEGE + SEGF;
            break;
        case 'M':
        case 'm':
            return SEGA + SEGC + SEGE;
            break;
        case 'N':
        case 'n':
            return SEGC + SEGE + SEGG;
            break;
        case 'O':
        case 'o':
        case '0':
            return SEGA + SEGB + SEGC + SEGD + SEGE + SEGF;
            break;
        case 'P':
        case 'p':
            return SEGA + SEGB + SEGE + SEGF + SEGG;
            break;
        case 'Q':
        case 'q':
            return SEGA + SEGB + SEGC + SEGF + SEGG;
            break;
        case 'R':
        case 'r':
            return SEGE + SEGG;
            break;
        case 'S':
        case 's':
            return SEGA + SEGC + SEGD + SEGF;
            break;
        case 'T':
        case 't':
            return SEGD + SEGE + SEGF + SEGG;
            break;
        case 'U':
        case 'u':
            return SEGB + SEGC + SEGD + SEGE + SEGF;
            break;
        case 'V':
        case 'v':
            return SEGC + SEGD + SEGE;
            break;
        case 'W':
        case 'w':
            return SEGB + SEGD + SEGF;
            break;
        case 'Y':
        case 'y':
            return SEGB + SEGC + SEGD + SEGF + SEGG;
            break;
        case 'Z':
        case 'z':
            return SEGA + SEGB + SEGD + SEGE;
            break;
        default :
            return 0;
    }
}
