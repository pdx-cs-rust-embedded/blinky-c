# microbian/Makefile
# Copyright (c) 2020 J. M. Spivey
# Heavily edited by Bart Massey 2023.

CHIP = cortex-m4
LSCRIPT = nRF52833.ld

CPU = -mcpu=$(CHIP) -mthumb
CFLAGS = -O -g -Wall -ffreestanding
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
AR = arm-none-eabi-ar

all: blinky.elf

%.hex: %.elf
	arm-none-eabi-objcopy -O ihex $< $@

%.elf: %.o
	$(CC) $(CPU) $(CFLAGS) -T $(LSCRIPT) -nostdlib $^ -lc -lgcc -o $@

%.o: %.c
	$(CC) $(CPU) $(CFLAGS) -c $< -o $@ 

%.o: %.s
	$(AS) $(CPU) $< -o $@

%.s: %.c
	$(CC) $(CPU) $(CFLAGS) -S -c $< -o $@ 

clean:
	-rm -f *.o *.elf *.hex

blinky.elf: blinky.o startup.o

blinky.o: hardware.h blinky.c
