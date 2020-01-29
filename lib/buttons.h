#ifndef H_BUTTONS
#define H_BUTTONS

#define BUTTON_PORT        GPIOA
#define BUTTON_READ        GPIOA_IDR
#define SET_PIN            GPIO9
#define CHOOSE_PIN         GPIO10

void buttonsInit(void);
void checkButtonResetTimer(void);
void startButtonsCheck(void);

#endif
