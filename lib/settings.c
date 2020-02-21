#include "../libopencm3/include/libopencm3/stm32/flash.h"
#include "../libopencm3/include/libopencm3/stm32/f0/nvic.h"
#include "settings.h"
#include "tl.h"
#include "menu.h"

extern volatile tlParams tlPar;
extern volatile menuSettings menuSet;

void waitForLastOperation(void);
void programWord(uint32_t address, uint32_t data);
void programHalfWord(uint32_t address, uint16_t data);
void erasePage(uint32_t page_address);

void setInit()
{
    flash_set_ws(0x000000001);
//    FLASH_CR |= FLASH_CR_ERRIE;
//    nvic_enable_irq(NVIC_FLASH_IRQ);
//    nvic_set_priority(NVIC_FLASH_IRQ, 0x00);
    menuSet.state = loadSettings();
}

volatile uint32_t saveCnt = 0;
void saveSettings()
{
    ++saveCnt;
//    erasePage(SET_ADDR);
/*
    uint32_t setAddr = SET_ADDR;
    programWord(setAddr, tlPar.setVoltage);
    setAddr += 4;
    programWord(setAddr, tlPar.setCurrent);
    setAddr += 4;
    programHalfWord(setAddr, menuSet.state); */
}

volatile uint32_t loadCnt = 0;
uint8_t loadSettings()
{
    ++loadCnt;
    uint32_t param32;
    param32 = MMIO32(SET_ADDR);
    if( param32 > tlPar.maxVoltage ) {
        tlPar.setVoltage = 0;
    } else {
        tlPar.setVoltage = param32;
    }
    param32 = MMIO32(SET_ADDR + 4);
    if( param32 > tlPar.maxCurrent ) {
        tlPar.setCurrent = 0;
    } else {
        tlPar.setCurrent = param32;
    }

    uint16_t param16 = MMIO16(SET_ADDR + 8);
    uint8_t retState;
    switch( param16 )
    {
        case MANUAL_VOLTAGE:
        case MANUAL_CURRENT:
        case CHARGER_6:
        case CHARGER_12:
            retState = (uint8_t)param16;
            break;
        default:
            retState = MANUAL_VOLTAGE;
            break;
    }
    return retState;
}


// отличие функций от стандартных libopencm3 в таймауте
volatile uint32_t maxTimeout = 0;
void waitForLastOperation()
{
    uint32_t timeout = 1e4;
    while ( ((flash_get_status_flags() & FLASH_SR_BSY) == FLASH_SR_BSY) &&
            (--timeout > 5) );
    if( (1e4 - timeout) > maxTimeout ) maxTimeout = 1e4 - timeout;
}


void programWord(uint32_t address, uint32_t data)
{
    programHalfWord(address, (uint16_t)data);
    programHalfWord(address+2, (uint16_t)(data>>16));
}


void programHalfWord(uint32_t address, uint16_t data)
{
    flash_unlock();
    waitForLastOperation();
    FLASH_CR |= FLASH_CR_PG;

	MMIO16(address) = data;

    waitForLastOperation();
	FLASH_CR &= ~FLASH_CR_PG;
    flash_lock();
}

volatile uint32_t t1 = 0;
void erasePage(uint32_t page_address)
{
    flash_unlock();
    waitForLastOperation();
	FLASH_CR |= FLASH_CR_PER;
    t1 = page_address;
	FLASH_AR = page_address;
	FLASH_CR |= FLASH_CR_STRT;
    waitForLastOperation();
	FLASH_CR &= ~FLASH_CR_PER;
    flash_lock();
}
