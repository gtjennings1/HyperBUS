# HyperRAM
A basic HyperRAM controller for Lattice iCE40 Ultraplus FPGAs

You can download a Verilog model of the Cypress HyperRAM from their website.
http://www.cypress.com/verilog/s27kl0641-verilog

​	bitstream/	- Contains pre-synthesized and compiled FPGA bitstream and RISC-V firmware files

​	radiant/		- Lattice Radiant project of the RISC-V + HyperRAM controller design

​	iCEStorm/	- iCEStorm project of the RISC-V + HyperRAM controller design

​	riscv32/		- picorv32 and picoSoC RISC-V files

​	simulation/	- Simulation of standalone controller

​	standalone/	- Simple HyperRam Controller

Sources:
RISC-V examples were based off of the PicoSoC examples provided by mmicko at the Hackaday FPGA101 Workshop.  Thank you for the great examples mmicko!
https://github.com/mmicko/fpga101-workshop


## How do I use this project

This project provide examples for APIO and iCEStorm projects and also The Lattice Radiant sotware.

### Build and upload under iCEStorm 
1. Install iCEStorm (http://www.clifford.at/icestorm/)
2. Run the following commands
    cd ./icestorm
    ./hyperram.sh
    iceprog hyperram.bin

### Build and upload under APIO project
1. Install APIO (https://github.com/FPGAwars/apio)
2. Run the following commands
    cd ./riscv32/hardware
    apio build
    apio upload

### Build and upload under Radiant software
1. Install the Laticce Radiant software (http://www.latticesemi.com/Products/DesignSoftwareAndIP/FPGAandLDS/Radiant)
2. Open radiant/riscv32_radiant.rdf file
3. Build and upload the project using the Radiant Software

### Build and upload the software for RISCV32 
1. If you use the APIO project:
    cd ./riscv32/software
    apio make
    apio make upload

2. In other cases 
   riscv64-unknown-elf-gcc -O3 -nostartfiles -mabi=ilp32 -march=rv32ic -Wl,-Bstatic,-T,sections.lds,--strip-debug -ffreestanding -o firmware.elf start.s sections.c firmware.c -lgcc
   riscv64-unknown-elf-objcopy  -O binary firmware.elf firmware.bin

3. Upload firmware.bin
* iCEStorm:
    iceprog -o 1M firmware.bin
* Radiant: upload the firmware.bin file using the programmer tool. The start address should be 1MB (see readme.md in bitstream/)

## Project Description

FPGA Project contains a RISC-V core with the hyperram controller connected.  Write and read tests are performed on the memory.

- On power up, the RGB LED will light up red
  - This insures the FPGA bitstream is loaded properly and that the RISC-V code in SPI Flash is executing.

- Shortly after words the RGB LED will flash blue or green
  - Green = read/write tests are passing
  - Blue = read/write tests are failing

Additionally, there is a UART TX port on pin 36.  If you connect it to a terminal window you can monitor the tests.  You can use the Adafruit FT232H USB board for this and connect a fly wire between pin 38 on the UPDuino and D1 and a ground wire between both boards.  Set the baud rate to 9600.