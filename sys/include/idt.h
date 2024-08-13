#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include "../../utils/include/string.h"
#include "../../utils/include/io.h"
#include "../../drivers/include/serial.h"
#include "../../drivers/include/vga.h"
#include "../../utils/include/intreg.h"

#define PIC1 0x20 /* IO base address for master PIC */
#define PIC2 0xA0 /* IO base address for slave PIC */
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)
#define PIC_EOI 0x20

#define ICW4_8086 0x01        /* 8086/88 (MCS-80/85) mode */
#define IDT_FLAGS 0x8E        // 1(P/Present)00(DPL)0(Always 0) 1110(Gate Type)
#define GDT_CODE_SEGMENT 0x08 // 0000 1000 (Selector for Code Segment which we defined in GDT)

#define IDT_SIZE 256 // 0..255

struct IDT_Entry
{
    uint16_t base_low;  // offset bits 0..15 (offset 1)
    uint16_t selector;  // a code segment selector in GDT or LDT
    uint8_t zero;       // unused, set to 0 (always 0)
    uint8_t flags;      // gate type, dpl, and p fields (type_attributes)
    uint16_t base_high; // offset bits 16..31 (offset 2)
} __attribute__((packed));

struct IDT_Locator
{
    uint32_t base_ptr; // offset
    uint16_t limit;
} __attribute__((packed));

void INIT_IDT();
void SET_IDT_GATE(uint8_t entry_num, uint32_t base, uint16_t sel, uint8_t flags);

// INTERRUPT SERVICE ROUTINES
void INIT_ISR();
void ISR_HANDLER(struct InterruptRegisters *r);

// IRQ HANDLERS
void REMAP_PIC();
void IRQ_INIT_HANDLER(int irq, void (*handler)(struct InterruptRegisters *));
void IRQ_RESET_HANDLER(int irq);
void IRQ_HANDLER(struct InterruptRegisters *reg);
void INIT_IRQ();

// // INTERRUPT SERVICE ROUTINES
// extern void isr0();
// extern void isr1();
// extern void isr2();
// extern void isr3();
// extern void isr4();
// extern void isr5();
// extern void isr6();
// extern void isr7();
// extern void isr8();
// extern void isr9();
// extern void isr10();
// extern void isr11();
// extern void isr12();
// extern void isr13();
// extern void isr14();
// extern void isr15();
// extern void isr16();
// extern void isr17();
// extern void isr18();
// extern void isr19();
// extern void isr20();
// extern void isr21();
// extern void isr22();
// extern void isr23();
// extern void isr24();
// extern void isr25();
// extern void isr26();
// extern void isr27();
// extern void isr28();
// extern void isr29();
// extern void isr30();
// extern void isr31();

// extern void isr128();
// extern void isr177();

// // IRQ HANDLERS

// extern void irq0();
// extern void irq1();
// extern void irq2();
// extern void irq3();
// extern void irq4();
// extern void irq5();
// extern void irq6();
// extern void irq7();
// extern void irq8();
// extern void irq9();
// extern void irq10();
// extern void irq11();
// extern void irq12();
// extern void irq13();
// extern void irq14();
// extern void irq15();

#endif