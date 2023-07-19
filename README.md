# blinky-c
Bart Massey 2023

This uses the startup code and link scripts from
<https://github.com/Spivoxity/microbian> to run a C blinky
on the Micro:Bit v2.

To use, use the supplied `Makefile` to build `blinky.elf`,
then

    pyocd-flashtool -t nrf52 blinky.elf

The `openocd.cfg` file supplied will work with OpenOCD to
debug the program.
