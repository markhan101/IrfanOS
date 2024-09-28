#ifndef SERIAL_H
#define SERIAL_H

#include "../../utils/include/io.h"
#include "../../utils/include/string.h"

#define PORT 0x3f8 // COM1

int init_serial();
int serial_received();
char read_serial();
int is_transmit_empty();
void write_serial(char *a);
void write_serial_dec(int num);
void write_serial_hex(int num);

#endif // SERIAL_H
