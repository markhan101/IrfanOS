// #include "include/timer.h"

// void TIMER_INTERRUPT_HANDLER()
// {
//     // Acknowledge the interrupt to the PIC
//     outPort_B(PIC1_COMMAND, 0x20); // Send End of Interrupt (EOI) signal to PIC

//     // Example: Increment a tick counter
//     static uint32_t tick = 0;
//     tick++;

//     // Optionally, print something for debugging
//     if (tick % 1000 == 0)
//     {
//         write_serial("Timer tick: ");
//         char buffer[32];
//         itoa(tick, buffer, 10);
//         write_serial(buffer);
//         write_serial("\n");
//     }
// }
// void INIT_TIMER()
// {
//     uint32_t divisor = PIT_FREQ / TIMER_FREQ;

//     // 0x36 = 0011 0110
//     outPort_B(MODE_CMD_W, 0x36); // Set the PIT to the desired frequency

//     // send the frequency divisor as it goes in 8 bits
//     outPort_B(CH_0_RW, (uint8_t)(divisor));
//     outPort_B(CH_0_RW, (uint8_t)(divisor >> 8));

//     // SET_IRQ_HANDLER(0, TIMER_INTERRUPT_HANDLER);
// }
