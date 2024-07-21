# blinky-c
Bart Massey 2023

This uses the startup code and link scripts from
<https://github.com/Spivoxity/microbian> to run a C blinky
on the Micro:Bit v2. 

To build and run this code, you'll need `pyocd` (Debian
package `python3-pyocd` or `pip install pyocd`) and
`arm-none-eabi-gcc` (Debian package `gcc-arm-none-eabi`).

Use the supplied `Makefile` to build `blinky.elf`, then

    pyocd load -t nrf52 blinky.elf

The `openocd.cfg` file supplied will work with OpenOCD to
debug the program.
