#ifndef IO_H
#define IO_H

#include <stdint.h>

void outPort_B(uint16_t port, uint8_t value);

uint8_t inPort_B(uint16_t port);

void io_Wait();

#endif