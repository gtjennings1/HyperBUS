python bincombine.py -o combine.bin 0x0 hardware.bin 0x100000 firmware.bin

I had some trouble loading the firmware.bin with radiant and diamond programmer. So, I used this combiner script.

You have to manually enter the size of combine.bin which is 1053736 bytes for the firmware that is checked in.  You also have to set the end address to 0x110000