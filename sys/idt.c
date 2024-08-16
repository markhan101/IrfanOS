#include "include/idt.h"

struct IDT_Entry idt_entries[IDT_SIZE];
struct IDT_Locator idt_ptr;

void IDT_FLUSH_AND_LOAD(uint32_t);

void SET_IDT_GATE(uint8_t entry_num, uint32_t base, uint16_t sel, uint8_t flags)
{

    idt_entries[entry_num].base_low = base & 0xFFFF;
    idt_entries[entry_num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[entry_num].selector = sel;
    idt_entries[entry_num].zero = 0;
    idt_entries[entry_num].flags = flags | 0x60;
}

void INIT_IDT()
{

    terminal_writestring("Initializing IDT...\n");
    idt_ptr.base_ptr = (uint32_t)&idt_entries;
    idt_ptr.limit = (sizeof(struct IDT_Entry) * IDT_SIZE) - 1; // subtract 1 to get to the proper address which originally will have an offset of 1

    memset(&idt_entries, sizeof(struct IDT_Entry) * IDT_SIZE, 0);
    IDT_FLUSH_AND_LOAD((uint32_t)&idt_ptr);
}

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void INIT_ISR()
{

    SET_IDT_GATE(0, (unsigned)isr0, 0x08, 0x8E);
    SET_IDT_GATE(1, (unsigned)isr1, 0x08, 0x8E);
    SET_IDT_GATE(2, (unsigned)isr2, 0x08, 0x8E);
    SET_IDT_GATE(3, (unsigned)isr3, 0x08, 0x8E);
    SET_IDT_GATE(4, (unsigned)isr4, 0x08, 0x8E);
    SET_IDT_GATE(5, (unsigned)isr5, 0x08, 0x8E);
    SET_IDT_GATE(6, (unsigned)isr6, 0x08, 0x8E);
    SET_IDT_GATE(7, (unsigned)isr7, 0x08, 0x8E);
    SET_IDT_GATE(8, (unsigned)isr8, 0x08, 0x8E);
    SET_IDT_GATE(9, (unsigned)isr9, 0x08, 0x8E);
    SET_IDT_GATE(10, (unsigned)isr10, 0x08, 0x8E);
    SET_IDT_GATE(11, (unsigned)isr11, 0x08, 0x8E);
    SET_IDT_GATE(12, (unsigned)isr12, 0x08, 0x8E);
    SET_IDT_GATE(13, (unsigned)isr13, 0x08, 0x8E);
    SET_IDT_GATE(14, (unsigned)isr14, 0x08, 0x8E);
    SET_IDT_GATE(15, (unsigned)isr15, 0x08, 0x8E);
    SET_IDT_GATE(16, (unsigned)isr16, 0x08, 0x8E);
    SET_IDT_GATE(17, (unsigned)isr17, 0x08, 0x8E);
    SET_IDT_GATE(18, (unsigned)isr18, 0x08, 0x8E);
    SET_IDT_GATE(19, (unsigned)isr19, 0x08, 0x8E);
    SET_IDT_GATE(20, (unsigned)isr20, 0x08, 0x8E);
    SET_IDT_GATE(21, (unsigned)isr21, 0x08, 0x8E);
    SET_IDT_GATE(22, (unsigned)isr22, 0x08, 0x8E);
    SET_IDT_GATE(23, (unsigned)isr23, 0x08, 0x8E);
    SET_IDT_GATE(24, (unsigned)isr24, 0x08, 0x8E);
    SET_IDT_GATE(25, (unsigned)isr25, 0x08, 0x8E);
    SET_IDT_GATE(26, (unsigned)isr26, 0x08, 0x8E);
    SET_IDT_GATE(27, (unsigned)isr27, 0x08, 0x8E);
    SET_IDT_GATE(28, (unsigned)isr28, 0x08, 0x8E);
    SET_IDT_GATE(29, (unsigned)isr29, 0x08, 0x8E);
    SET_IDT_GATE(30, (unsigned)isr30, 0x08, 0x8E);
    SET_IDT_GATE(31, (unsigned)isr31, 0x08, 0x8E);
}

char *exception_messages[] =
    {
        "Division by Zero",
        "Debug",
        "Non Maskable Interrupt",
        "Breakpoint",
        "Into Detected Overflow",
        "Out of Bounds",
        "Invalid Opcode",
        "No Coprocessor",
        "Double Fault",
        "Coprocessor Segment Overrun",
        "Bad TSS",
        "Segment Not Present",
        "Stack Fault",
        "General Protection Fault",
        "Page Fault",
        "Unknown Interrupt",
        "Coprocessor Fault",
        "Alignment Check",
        "Machine Check",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved"};

void ISR_HANDLER(struct InterruptRegisters *r)
{
    if (r->int_no < 32)
    {

        terminal_writestring("\n\n*** [Kernel panic - ");
        terminal_writestring(exception_messages[r->int_no]);
        terminal_writestring(" Exception] ***\nInterrupt error code ");
        terminal_writestring("\nHalting!\n");

        for (;;)
            ;
    }
}

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
        outPort_B(0xA0, 0x20); // Send EOI to the slave PIC
    }

    outPort_B(0x20, 0x20); // Send EOI to the master PIC
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