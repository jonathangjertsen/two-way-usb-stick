# Two way USB stick

Given an oscilloscope which stores its screenshots to a USB stick, I need a way to access those screenshots
without physically moving the USB stick from the scope to the PC and back

To solve this, make a device with 2 USB interfaces. One goes into the scope, the other goes into the PC.
The device provides a regular FAT filesystem to the oscilloscope interface, and a read-only filesystem to the same
data on the other interface.

I have a NUCLEO-H743ZI development board containing a STM32H743ZI MCU.
The MCU has two USB OTG interfaces, should be just what I need
