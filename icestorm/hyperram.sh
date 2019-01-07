yosys -p "synth_ice40 -blif hyperram.blif" ../riscv32/hardware/top.v ../riscv32/hardware/wdt.v ../riscv32/hardware/flash_io.v ../standalone/hbc.v ../standalone/hbc_io.v ../riscv32/hardware/picosoc.v ../riscv32/hardware/pll.v ../riscv32/hardware/simpleuart.v ../riscv32/hardware/spimemio.v ../riscv32/hardware/zpicorv32.v
arachne-pnr -d 5k -P sg48 -p ../riscv32/hardware/pinout.pcf hyperram.blif -o hyperram.asc
icepack hyperram.asc hyperram.bin


