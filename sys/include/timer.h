#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stddef.h>
#include "../../utils/include/intreg.h"
#include "../../drivers/include/serial.h"
#include "../../utils/include/io.h"
#include "idt.h"

#define CH_0_RW 0x40
#define CH_1_RW 0x41
#define CH_2_RW 0x42
#define MODE_CMD_W 0x43 // MODE/COMMAND REGISTER WRITE

#define TIMER_FREQ 100

void INIT_TIMER();
void SET_IRQ_0(struct InterruptRegisters *r);

#endif