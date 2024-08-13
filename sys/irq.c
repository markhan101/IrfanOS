#include "include/idt.h"

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void REMAP_PIC()
{
    // ICW1: Start initialization of PIC
    outPort_B(PIC1, 0x11);
    outPort_B(PIC2, 0x11);

    // ICW2: Set interrupt vector offsets
    outPort_B(PIC1_DATA, 0x20);
    outPort_B(PIC2_DATA, 0X28);

    outPort_B(PIC1_DATA, 0x04); // ICW3: Tell Master PIC there is a slave PIC at IRQ2 (0000 0100)
    outPort_B(PIC2_DATA, 0x02); // Tell Slave PIC its cascade identity (0000 0010)

    // ICW4: Set PIC to x86 mode
    outPort_B(PIC1_DATA, ICW4_8086);
    outPort_B(PIC2_DATA, ICW4_8086);

    // Mask interrupts on both PICs
    outPort_B(PIC1_DATA, 0);
    outPort_B(PIC2_DATA, 0);
}

void *IRQ_ROUTINES[16] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// event handler for IRQs
void IRQ_INIT_HANDLER(int irq, void (*handler)(struct InterruptRegisters *))
{
    IRQ_ROUTINES[irq] = handler;
}

void IRQ_RESET_HANDLER(int irq)
{
    IRQ_ROUTINES[irq] = 0;
}

void IRQ_HANDLER(struct InterruptRegisters *reg)
{
    void (*handler)(struct InterruptRegisters *reg); // Declare a function pointer

    handler = IRQ_ROUTINES[reg->int_no - 32]; // Get the handler for the specific IRQ
    if (handler)
    {
        handler(reg); // Call the handler if it exists
    }

    if (reg->int_no >= 40) // Check if the interrupt is from the slave PIC
    {
        outb(0xA0, 0x20); // Send EOI to the slave PIC
    }

    outb(0x20, 0x20); // Send EOI to the master PIC
}

void INIT_IRQ()
{
    REMAP_PIC();

    SET_IDT_GATE(32, (unsigned)irq0, 0x08, 0x8E);
    SET_IDT_GATE(33, (unsigned)irq1, 0x08, 0x8E);
    SET_IDT_GATE(34, (unsigned)irq2, 0x08, 0x8E);
    SET_IDT_GATE(35, (unsigned)irq3, 0x08, 0x8E);
    SET_IDT_GATE(36, (unsigned)irq4, 0x08, 0x8E);
    SET_IDT_GATE(37, (unsigned)irq5, 0x08, 0x8E);
    SET_IDT_GATE(38, (unsigned)irq6, 0x08, 0x8E);
    SET_IDT_GATE(39, (unsigned)irq7, 0x08, 0x8E);
    SET_IDT_GATE(40, (unsigned)irq8, 0x08, 0x8E);
    SET_IDT_GATE(41, (unsigned)irq9, 0x08, 0x8E);
    SET_IDT_GATE(42, (unsigned)irq10, 0x08, 0x8E);
    SET_IDT_GATE(43, (unsigned)irq11, 0x08, 0x8E);
    SET_IDT_GATE(44, (unsigned)irq12, 0x08, 0x8E);
    SET_IDT_GATE(45, (unsigned)irq13, 0x08, 0x8E);
    SET_IDT_GATE(46, (unsigned)irq14, 0x08, 0x8E);
    SET_IDT_GATE(47, (unsigned)irq15, 0x08, 0x8E);
}