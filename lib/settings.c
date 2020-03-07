#include "../libopencm3/include/libopencm3/stm32/flash.h"
#include "../libopencm3/include/libopencm3/stm32/f0/nvic.h"
#include "../libopencm3/include/libopencm3/stm32/timer.h"
#include "../libopencm3/include/libopencm3/stm32/rcc.h"
#include "tl.h"
#include "menu.h"
#include "settings.h"

extern volatile tlParams tlPar;
extern volatile menuSettings menuSet;

void waitForLastOperation(void);
void programWord(uint32_t address, uint32_t data);
void programHalfWord(uint32_t address, uint16_t data);
void erasePage(uint32_t page_address);

void setInit()
{
    flash_set_ws(0x000000001);
    FLASH_CR |= FLASH_CR_ERRIE;
    nvic_enable_irq(NVIC_FLASH_IRQ);
    nvic_set_priority(NVIC_FLASH_IRQ, 0x00);
    menuSet.state = loadSettings();
}


void saveSettings()
{
    erasePage(SET_ADDR);
    uint32_t setAddr = SET_ADDR;
    programWord(setAddr, tlPar.setVoltage);
    setAddr += 4;
    programWord(setAddr, tlPar.setCurrent);
    setAddr += 4;
    programHalfWord(setAddr, menuSet.state);
}

uint8_t isEqual()
{
    uint32_t param32 = MMIO32(SET_ADDR);
    param32 ^= tlPar.setVoltage;
    uint32_t sum = param32;
    param32 = MMIO32(SET_ADDR + 4);
    sum += tlPar.setCurrent;
    uint16_t param16 = MMIO16(SET_ADDR + 8);
    param16 ^= menuSet.state;
    sum += param16 & 0x00ff;
    if( sum ) return 0;
    else      return 1;
}


uint8_t loadSettings()
{
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
void waitForLastOperation()
{
    uint32_t timeout = 1e5;
    asm("NOP");
    asm("NOP");
    while ( ((flash_get_status_flags() & FLASH_SR_BSY) == FLASH_SR_BSY) &&
            (--timeout > 5) );
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
    FLASH_SR |= FLASH_SR_EOP;
	FLASH_CR &= ~FLASH_CR_PG;
    flash_lock();
}


void erasePage(uint32_t page_address)
{
    flash_unlock();
    waitForLastOperation();
	FLASH_CR |= FLASH_CR_PER;
	FLASH_AR = page_address;
	FLASH_CR |= FLASH_CR_STRT;
    waitForLastOperation();
    FLASH_SR |= FLASH_SR_EOP;
	FLASH_CR &= ~FLASH_CR_PER;
    flash_lock();
}
