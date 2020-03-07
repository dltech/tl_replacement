#ifndef SETTINGS_H
#define SETTINGS_H

#define SET_ADDR    0x08003c00

void setInit(void);
void saveSettings(void);
uint8_t loadSettings(void);
uint8_t isEqual(void);



#endif
