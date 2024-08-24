#include "include/serial.h"

int init_serial()
{
    outPort_B(PORT + 1, 0x00); // Disable all interrupts
    outPort_B(PORT + 3, 0x80); // Enable DLAB (set baud rate divisor)
    outPort_B(PORT + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    outPort_B(PORT + 1, 0x00); //                  (hi byte)
    outPort_B(PORT + 3, 0x03); // 8 bits, no parity, one stop bit
    outPort_B(PORT + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    outPort_B(PORT + 4, 0x0B); // IRQs enabled, RTS/DSR set
    outPort_B(PORT + 4, 0x1E); // Set in loopback mode, test the serial chip
    outPort_B(PORT + 0, 0xAE); // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if (inPort_B(PORT + 0) != 0xAE)
    {
        return 1;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    outPort_B(PORT + 4, 0x0F);
    return 0;
}

int serial_received()
{
    return inPort_B(PORT + 5) & 1;
}

char read_serial()
{
    while (serial_received() == 0)
        ;

    return inPort_B(PORT);
}

int is_transmit_empty()
{
    return inPort_B(PORT + 5) & 0x20;
}

void write_serial(char *msg)
{
    while (is_transmit_empty() == 0)
        ;

    while (*msg)
    {
        outPort_B(PORT, *msg);
        msg++;
    }
}
