/* common/nRF52833.ld */
/* Copyright (c) 2018-20 J. M. Spivey */

MEMORY {
    FLASH   (rx)  : ORIGIN = 0x00000000,      LENGTH = 512K
    RAM     (rwx) : ORIGIN = 0x20000000,      LENGTH = 124K
    CODERAM (rwx) : ORIGIN = 0x00800000+124K, LENGTH = 4K
}

OUTPUT_FORMAT ("elf32-littlearm")

/* Setting the entry address helps GDB to find the stack bottom */
ENTRY(start)

SECTIONS {
    .text ALIGN(16) : SUBALIGN(16) {
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
        __etext = .;
    } > FLASH

    .xram : AT (LOADADDR(.text) + SIZEOF(.text)) {
        __xram_start = .;
        *(.xram*)
        . = ALIGN(4);
        __xram_end = .;
    } > CODERAM

    .data : AT (LOADADDR(.xram) + SIZEOF(.xram)) {
        __data_start = .;
        *(.data*)
        . = ALIGN(4);
        __data_end = .;
    } > RAM

    .bss : {
        __bss_start = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .;
        __end = .;
    } > RAM

    /* Set stack top to end of RAM, and move stack limit down by
       size of stack */
    __stack = ORIGIN(RAM) + LENGTH(RAM);
    __stack_limit = __stack - 2048;

    /* Check if data + stack exceeds RAM limit */
    ASSERT(__stack_limit >= __end, "region RAM overlaps with stack")
}
