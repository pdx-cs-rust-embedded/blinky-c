/* blinky.c */
/* Copyright (c) 2018 J. M. Spivey */
/* Heavily modified Bart Massey 2023. */

#include "hardware.h"

void spin(void);

/* The next routines can be used in C compiler output, even
if not mentioned in the source. */

/* memcpy -- copy n bytes from src to dest (non-overlapping) */
void *memcpy(void *dest, const void *src, unsigned n)
{
    unsigned char *p = dest;
    const unsigned char *q = src;
    while (n-- > 0) *p++ = *q++;
    return dest;
}

/* memset -- set n bytes of dest to byte x */
void *memset(void *dest, unsigned x, unsigned n)
{
    unsigned char *p = dest;
    while (n-- > 0) *p++ = x;
    return dest;
}

unsigned volatile * const gpio_base[2] = {
    GPIO0_BASE, GPIO1_BASE
};

/* Addresses set by the linker */
extern unsigned char __xram_start[], __xram_end[],
    __data_start[], __data_end[], __bss_start[], __bss_end[],
    __etext[], __stack[];

void init(void)
{
    /* Activate the crystal clock */
    CLOCK_HFCLKSTARTED = 0;
    CLOCK_HFCLKSTART = 1;
    while (! CLOCK_HFCLKSTARTED) { }

    /* Enable the instruction cache */
    SET_BIT(NVMC_ICACHECONF, NVMC_ICACHECONF_CACHEEN);

    /* Copy xram and data segments and zero out bss. */
    int xram_size = __xram_end - __xram_start;
    int data_size = __data_end - __data_start;
    int bss_size = __bss_end - __bss_start;
    memcpy(__xram_start, __etext, xram_size);
    memcpy(__data_start, __etext+xram_size, data_size);
    memset(__bss_start, 0, bss_size);

    spin();
}

/* delay_loop -- timed delay */
void delay_loop(unsigned usecs)
{
    /* Without executing from RAM, this delay loop may go slowly, but
       it isn't used anywhere it matters. */
    unsigned t = usecs << 4;
    while (t > 0) {
        /* 62.5nsec per iteration */
        nop();
        t--;
    }
}

/* spin -- show Seven Stars of Death */
void spin(void)
{
    /* The SSOD was easy on micro:bit-v1 and is harder on v2, but it
       has proven so popular that it is worth the effort to keep it.
       We assume the icache is enabled -- if not, the flashing will
       just go at about half speed. */

    int i, k;

    static const unsigned ssod[] = {
        _ROW(ROW1, 0,1,0,1,0),
        _ROW(ROW3, 1,0,1,0,1),
        _ROW(ROW5, 0,1,0,1,0)
    };

    intr_disable();

    GPIO0_DIR = LED_MASK0;
    GPIO1_DIR = LED_MASK1;
    
    while (1) {
        for (k = 33; k > 0; k--) { /* 0.5s on */
            for (i = 0; i < 6; i += 2) { /* 15ms per loop */
                GPIO0_OUT = ssod[i];
                GPIO1_OUT = ssod[i+1];
                delay_loop(5000);
            }
        }
        GPIO0_OUT = 0;
        GPIO0_OUT = 0;
        delay_loop(100000); /* 0.1s off */
    }          
}
