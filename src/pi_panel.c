#include <pigpio.h>
#include "pi_panel.h"

#define LEDdPIN  16
#define LEDlPIN  20
#define LEDcPIN  21
#define SWdPIN  19
#define SWlPIN  13
#define SWcPIN  26
#define MSBFIRST  1

void rpi_init()
{
    gpioInitialise ();     //Setup the library
    gpioSetMode(LEDlPIN,PI_OUTPUT);
    gpioSetMode(LEDlPIN, PI_OUTPUT);
	gpioSetMode(LEDcPIN, PI_OUTPUT);
	gpioSetMode(SWdPIN, PI_INPUT);
	gpioSetMode(SWcPIN, PI_INPUT);
	gpioSetMode(SWlPIN, PI_OUTPUT);

    int LEDout = bbI2COpen(LEDcPIN,LEDdPIN,100000);
    int SWOut = bbI2COpen(SWcPIN,SWdPIN,100000);

}

uint8_t reverse_lut[16] = {  0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe, 0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf };

void read_write_panel(uint8_t status, uint8_t data, uint16_t bus, uint16_t *bus_switches, uint8_t *cmd_switches, uint8_t write)
{
    // status (byte, but will likely need to be a word) = 0
    // data (byte) = cpu.data_bus
    // bus (word) = cpu.address_bus
    // *bus _switches (word) = &bus_switches
    // *cmd_switches (byte, but will likely need to be a word)  &cmd_switches
    // write (byte) = 1 
	uint32_t out;

    //This was used to match up the code to the panel
	//status = reverse_lut[(status & 0xf0) >> 4]  | reverse_lut[status & 0xf] << 4;
	//data = reverse_lut[(data & 0xf0) >> 4] | reverse_lut[data & 0xf] << 4;
	//bus = reverse_lut[(bus & 0xf000) >> 12] << 8 | reverse_lut[(bus & 0x0f00) >> 8] << 12 |  reverse_lut[(bus & 0xf0) >> 4] | reverse_lut[bus & 0xf] << 4;
	//out = status << 24 | data << 16 | bus;

	if(write) {
       // take the latchPin low so
       // the LEDs don't change while you're sending in bits:
        gpioWrite(LEDlPIN, PI_LOW);
       // Now push data to 74HC595

       shiftOut(LdataPin,LclockPin,MSBFIRST,status >> 8);
       shiftOut(LdataPin,LclockPin,MSBFIRST,bus >> 8);
       shiftOut(LdataPin,LclockPin,MSBFIRST,bus);
       shiftOut(LdataPin,LclockPin,MSBFIRST,status);
       shiftOut(LdataPin,LclockPin,MSBFIRST,data);
       // take the latch pin high so the LEDs will light up:
       digitalWrite(LlatchPin, HIGH);
    }
    
    //Write Pulse to Latch Pin
    digitalWrite(SWlPIN, False);
    delayMicroseconds(5);
    digitalWrite(SWlPIN, True);
    delayMicroseconds(5);
    uint8_t al = 0;
    uint8_t ah = 0;
    uint8_t cl = 0;
    uint8_t ch = 0;
    boolean bitVal = 0;
    
    // Now get data from 74HC165
    for(int i = 0; i < 8; i++)
    {
        bitVal = digitalRead(SWdPIN);
        al |= (bitVal << (7 - i));
        digitalWrite(SWcPIN, True);
        delayMicroseconds(10);
        digitalWrite(SWcPIN, False;
    }
   for(int i = 0; i < 8; i++)
   {
        bitVal = digitalRead(SWdPIN);
        ah |= (bitVal << (7 - i));

        digitalWrite(SWcPIN, True);
        delayMicroseconds(10);
        digitalWrite(SWcPIN, False);
    }
   for(int i = 0; i < 8; i++)
   {
        bitVal = digitalRead(SWdPIN);
        cl |= (bitVal << (7 - i));

        digitalWrite(SWcPIN, True);
        delayMicroseconds(10);
        digitalWrite(SWcPIN, False);
    }

   for(int i = 0; i < 8; i++)
   {
        bitVal = digitalRead(SWdPIN);
        ch |= (bitVal << (7 - i));

        digitalWrite(SWcPIN, True);
        delayMicroseconds(10);
        digitalWrite(SWcPIN, False);
    }

  *bus_switches = (ah<<8) + al;
  *cmd_switches = (ch<<8) + cl;
}
