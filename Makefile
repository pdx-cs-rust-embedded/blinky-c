# microbian/Makefile
# Copyright (c) 2020 J. M. Spivey
# Heavily edited by Bart Massey 2023.

CHIP = cortex-m4
LSCRIPT = nRF52833.ld

CPU = -mcpu=$(CHIP) -mthumb
CFLAGS = -Os -g
CC = arm-none-eabi-gcc -Wall -ffreestanding

all: blinky.elf

%.elf: %.o
	$(CC) $(CPU) $(CFLAGS) -T $(LSCRIPT) -nostdlib $^ -lc -lgcc -o $@

%.o: %.c
	$(CC) $(CPU) $(CFLAGS) -c $< -o $@ 

clean:
	-rm -f *.o *.elf

blinky.elf: blinky.o startup.o

blinky.o: hardware.h blinky.c
