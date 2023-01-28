#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "types.h"

/*#ifdef AVRONBOARD
#include "avr_pins.h"

// Memory calls to 23LC512 RAM
extern uint8_t cmd_switches;
extern uint16_t bus_switches;

inline uint8_t read8(uint16_t address)
{
unsigned char retval = 0;

  digitalWrite(RAMCS, LOW);
  shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,0x03);
  shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,((tmp16addr >> 8) & 255));
  shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,(tmp16addr & 255));
  retval = shiftIn(RAMdiPIN,RAMcPIN,MSBFIRST);

  digitalWrite(RAMCS, HIGH);
  return retval;
}
inline uint16_t read16(uint16_t address)
{
    // MSB in the lower byte
    uint8_t pgaddr = (tmp16addr >> 8) & 0xFF;
    // See if this is a read across a page
    if ((tmp16addr &  0x00FF) == 0xFF) pgaddr++; 

    unsigned char bretval = 0;
    digitalWrite(RAMCS, LOW);
    shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,0x03);
    shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,pgaddr);
    shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,(tmp16addr & 0x00FF));
    bretval = shiftIn(RAMdiPIN,RAMcPIN,MSBFIRST);
    digitalWrite(RAMCS, HIGH);

    unsigned short int retval = bretval << 8;
    //delayMicroseconds(Cdelay);
  
    digitalWrite(RAMCS, LOW);
    shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,0x03);
    shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,pgaddr);
    shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,(tmp16addr & 0x00FF)+1);
    bretval = shiftIn(RAMdiPIN,RAMcPIN,MSBFIRST);

    digitalWrite(RAMCS, HIGH);
    retval = retval + bretval;
    return retval;
}

void write8(uint16_t address, uint8_t val)
{
  digitalWrite(RAMCS, LOW);
  shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,0x02);
  shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,((tmp16addr >> 8) & 255));
  shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,(tmp16addr & 255));
  shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,vale);
  digitalWrite(RAMCS, HIGH);
  return;
}

inline void write16(uint16_t address, uint16_t val)
{
    // MSB in the lower byte
    
    uint8_t pgaddr = (tmp16addr >> 8) & 0xFF;
    // See if this is a write across a page
    if ((tmp16addr &  0x00FF) == 0xFF) pgaddr++; 

    digitalWrite(RAMCS, LOW);
    shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,0x02);
    shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,pgaddr);
    shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,(tmp16addr & 0xFF));
    shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,(vale >> 8));
    digitalWrite(RAMCS, HIGH);

    delayMicroseconds(Cdelay);
    digitalWrite(RAMCS, LOW);
    shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,0x02);
    shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,pgaddr);
    shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,(tmp16addr & 0x00FF)+1);
    shiftOut(RAMdoPIN,RAMcPIN,MSBFIRST,(vale & 0x00FF));
    digitalWrite(RAMCS, HIGH);
}
#else
*/
uint8_t read8(uint16_t address)
{
	uint8_t data;
        if(address < 64*1024)
                data =  memory[address];
	else
		data = 0;

        return data;
}

void write8(uint16_t address, uint8_t val)
{
        if(address < 64*1024)
                memory[address] = val;
}


uint16_t read16(uint16_t address)
{
        uint16_t result = 0;
        result = read8(address);
        result |= read8(address+1) << 8;

        return result;
}

void write16(uint16_t address, uint16_t val)
{
        write8(address, val & 0xff);
        write8(address+1, (val >> 8) & 0xff);
}
#endif