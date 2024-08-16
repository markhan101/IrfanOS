#include "include/timer.h"

uint64_t ticks;

void SET_IRQ_0(struct InterruptRegisters *r)
{
    ticks++;
    write_serial("Tickssss");
}

void INIT_TIMER()
{
    ticks = 0;
    IRQ_INIT_HANDLER(0, &SET_IRQ_0);

    uint32_t divisor = 1193182 / TIMER_FREQ;

    // 0x36 = 0011 0110
    outPort_B(MODE_CMD_W, 0x36); // Set the PIT to the desired frequency

    // send the frequency divisor as it goes in 8 bits
    outPort_B(CH_0_RW, (uint8_t)(divisor & 0xFF));
    outPort_B(CH_0_RW, (uint8_t)((divisor >> 8) & 0xFF));
}
