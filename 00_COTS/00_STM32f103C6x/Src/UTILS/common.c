/*************************************************************************/
// Author        : Sherif Ashraf Khedr
// Project       : Stm32f103c6x_Drivers
// File          : common.c
// Date          : Jan 8, 2024
// GitHub        : https://github.com/sherifkhadr
/*************************************************************************/

#include "common.h"


void Udelay_ms(uint16 milliseconds)
{
    // Adjust the multiplier based on your system clock frequency
    // This is just an example; you need to replace 16000000 with your actual clock frequency
    const uint32 cycles_per_ms = F_CPU / 1000UL;
    // Calculate the number of cycles required for the delay
    uint32 total_cycles = (uint32)milliseconds * cycles_per_ms;

    // Perform the busy-wait loop
    for (uint32 i = 0; i < total_cycles; i++)
    {
        asm volatile("nop");
    }
}
