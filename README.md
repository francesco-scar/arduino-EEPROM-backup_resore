# Arduino EEPROM backup restore
Simple script to backup entire EEPROM memory and restore it later.

This might be useful when you have some relevant configuration saved in EEPROM (such as some 3d printer configuration) but you want to upload another sketch without losing them.

# Usage

## Read EEPROM content
To read EEPROM content you can just comment (or leave commented) the `#define WRITE` at line 3 and upload the sketch on the Arduino board from which you want read the data. Once uploaded open the serial monitor, using 115200 as baud rate, and you will see the EEPROM content formatted as a c++ (decimal) integer array. If the reading is verified (comparing a checksum of consecutive readings) the `"Reading verified!"` string will be printed, otherwise try read the memory again.
