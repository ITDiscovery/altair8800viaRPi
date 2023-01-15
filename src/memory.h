#ifndef _MEMORY_H_
#define _MEMORY_H_
#include "types.h"
#endif

//#ifdef ARDUINO
/* #include "../arduino/pins.h"
inline void led_out(uint16_t address, uint8_t data, uint8_t status)
{
        digitalWrite(LEDlPIN,LOW);
        shiftOut(LEDdPIN,LEDcPIN,MSBFIRST,status >>8);
        shiftOut(LEDdPIN,LEDcPIN,MSBFIRST,address >>8);
        shiftOut(LEDdPIN,LEDcPIN,MSBFIRST,address);
        shiftOut(LEDdPIN,LEDcPIN,MSBFIRST,status);
        shiftOut(LEDdPIN,LEDcPIN,MSBFIRST,data);
}
inline uint8_t read8(uint16_t address)
{
        uint8_t data;


        return data;
}
inline uint16_t read16(uint16_t address)
{
        uint16_t result = 0;
        result = read8(address);
        result |= read8(address+1) << 8;

        return result;
}
inline void write16(uint16_t address, uint16_t val)
{
        write8(address, val & 0xff);
        write8(address+1, (val >> 8) & 0xff);
}
#else
*/
extern uint8_t memory[64*1024];
extern uint8_t cmd_switches;
extern uint16_t bus_switches;

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
//#endif