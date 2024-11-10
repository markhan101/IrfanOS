#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include "../../utils/include/string.h"
#include "../../utils/include/io.h"
#include "../../drivers/include/serial.h"
#include "../../drivers/include/vga.h"
#include "../../utils/include/intreg.h"

// IDT
#define IDT_SIZE 256          // 0..255
#define IDT_FLAGS 0x8E        // 1(P/Present)00(DPL)0(Always 0) 1110(Gate Type)
#define GDT_CODE_SEGMENT 0x08 // 0000 1000 (Selector for Code Segment which we defined in GDT)
#define RING_0_INTERRUPT_GATE 0x8E
#define RING_3_TRAP_GATE 0xEF

// IRQs
#define PIC1 0x20 /* IO base address for master PIC */
#define PIC2 0xA0 /* IO base address for slave PIC */
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

#define PIC_EOI 0x20 /* End-of-interrupt command code */

/* reinitialize the PIC controllers, giving them specified vector offsets
   rather than 8h and 70h, as configured by default */

#define ICW1_ICW4 0x01      /* Indicates that ICW4 will be present */
#define ICW1_SINGLE 0x02    /* Single (cascade) mode */
#define ICW1_INTERVAL4 0x04 /* Call address interval 4 (8) */
#define ICW1_LEVEL 0x08     /* Level triggered (edge) mode */
#define ICW1_INIT 0x10      /* Initialization - required! */

#define ICW4_8086 0x01       /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO 0x02       /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE 0x08  /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C /* Buffered mode/master */
#define ICW4_SFNM 0x10       /* Special fully nested (not) */

#define PIC_READ_IRR 0x0a /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR 0x0b /* OCW3 irq service next CMD read */

typedef struct
{
    uint16_t base_low;  // offset bits 0..15 (offset 1) of ISR
    uint16_t selector;  // a code segment selector in GDT or LDT
    uint8_t zero;       // unused, set to 0 (always 0)
    uint8_t flags;      // gate type, dpl, and p fields (type_attributes)
    uint16_t base_high; // offset bits 16..31 (offset 2) of ISR
} __attribute__((packed)) IDT_Entry;

typedef struct
{
    uint16_t limit;    // size of IDT
    uint32_t base_ptr; // offset
} __attribute__((packed)) IDT_Locator;

void INIT_IDT(void);
void IDT_SET_DESCRIPTOR(uint8_t vector, void *isr, uint8_t flags);

void PIC_SEND_EOI(uint8_t irq);
void PIC_REMAP(int offset1, int offset2);
void PIC_DISABLE();
void IRQ_SET_MASK(uint8_t IRQline);
void IRQ_CLEAR_MASK(uint8_t IRQline);
static uint16_t __PIC_GET_IRQ_REQ(int ocw3);
uint16_t PIC_GET_IRR();
uint16_t PIC_GET_ISR();

// IRQs

void SET_IRQ_HANDLER(uint8_t IRQ, void(*handler));

#endif // IDT_H