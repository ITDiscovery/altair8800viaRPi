altair8800
==========

What is this?
-------------

What started as a Intel 8080 emulator turned into a Altair 8800 emulator with associated hardware for a front panel. The hardware was an Uno, and is now an AVR128DB28, or via a Raspberry Pi. Both solutions use a 74HCT595 shift registers for LEDs and 74HCT165 for the switches.

The updated version of this project at https://github.com/dankar/nanoaltair8800 is not RPi compatible.  

Building
--------

The build for the Microchip AVR128DB28 is now up to date. It should work to run "./build" and then "make && upload" in the arduino folder to compile and program.

arduino-mk is used by the makefile.

The code will look for certain files on the SD card. "88dskrom.bin" is a disk bootloader which will be loaded to offset 0xff00 in memory. "disk1.bin" and "disk2.bin" will be used by the 88-DCDD emulator and will act as disk 1 and disk 2 respectively.

Completeness
------------

Passes Kelly Smith test and cputest.com. Runs CP/M and all kinds of BASIC I could find. Altair DOS not working for some reason (complains about insufficient memory). Support for 88-DCDD. No tape or cassette.

There are probably still a few bugs that needs ironing out.

I've removed the contention between RAM and SD Card, along with the fact that this board can run up 32MHz overclocked, I hope that this will run emulator runs at a speed close to the original Altair 8800. I'll be adding a way to stop execution once started with the RUN/STOP switch, previously, it's way too slow to check the front panel switches for each main loop.

Hardware
--------

A front panel has been designed and is available as a KiCad project under the PCB folder. The front panel is basically a bunch of shift registers for input from the switches and output to the LEDs, as well as a 23LC5612 SPI SRAM chip for memory and a MicroSD reader. 

Known bugs
----------



Raspberry Pi
------------

The current code in the repo now supports running on Raspberry Pi instead of Arduino. This means that the MicroSD slot is not necessary any more, as well as the SRAM chip. The code runs faster on a Raspberry Pi as well. I would recommend this route for anyone that wants to emulate more than just the Altair.

Todo
----

* Make the port IO more abstract instead of Altair 8800 specific.
* RUN/STOP switch enabled when running
