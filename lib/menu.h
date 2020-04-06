#ifndef H_MENU
#define H_MENU


enum menuState {
    MANUAL_VOLTAGE_NEWBIE = 1,
    MANUAL_VOLTAGE,
    MANUAL_VOLTAGE_CHANGED,
    MANUAL_CURRENT_NEWBIE,
    MANUAL_CURRENT,
    MANUAL_CURRENT_CHANGED,
    CHARGER_12_NEWBIE,
    CHARGER_12,
    CHARGER_6_NEWBIE,
    CHARGER_6,
    OFF
};

typedef struct {
    uint8_t state;
    int8_t handle;
    uint32_t cnt;
    uint8_t handleFlag;
    uint8_t setButFlag;
    uint8_t cvButFlag;
    uint8_t newFlag;
    uint8_t ovrFlag;
    uint8_t offFlag;
    const uint32_t updateFreq;
    const uint32_t changeTime;
} menuSettings;

#define HANDLE_DELTA    2

void checkHandle(void);
void menu(void);

#endif
