#include "include/idt.h"

struct IDT_Entry idt_entries[IDT_SIZE];
struct IDT_Locator idt_ptr;

void IDT_FLUSH_AND_LOAD(uint32_t);

static const char *isr_names[] = {
    "Division Error",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint ",
    "Overflow",
    "Out of Bo  unds",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved 22",
    "Reserved 23",
    "Reserved 24",
    "Reserved 25",
    "Reserved 26",
    "Reserved 27",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved 31"};

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

void INIT_IDT()
{

    terminal_writestring("Initializing IDT...\n");
    idt_ptr.base_ptr = (uint32_t)&idt_entries;
    idt_ptr.limit = (sizeof(struct IDT_Entry) * IDT_SIZE) - 1; // subtract 1 to get to the proper address which originally will have an offset of 1

    // set a chunk of memory
    memset(&idt_entries, sizeof(struct IDT_Entry) * IDT_SIZE, 0);

    REMAP_PIC();

    SET_IDT_GATE(0, (uint32_t)isr0, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(1, (uint32_t)isr1, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(2, (uint32_t)isr2, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(3, (uint32_t)isr3, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(4, (uint32_t)isr4, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(5, (uint32_t)isr5, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(6, (uint32_t)isr6, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(7, (uint32_t)isr7, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(8, (uint32_t)isr8, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(9, (uint32_t)isr9, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(10, (uint32_t)isr10, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(11, (uint32_t)isr11, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(12, (uint32_t)isr12, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(13, (uint32_t)isr13, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(14, (uint32_t)isr14, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(15, (uint32_t)isr15, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(16, (uint32_t)isr16, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(17, (uint32_t)isr17, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(18, (uint32_t)isr18, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(19, (uint32_t)isr19, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(20, (uint32_t)isr20, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(21, (uint32_t)isr21, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(22, (uint32_t)isr22, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(23, (uint32_t)isr23, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(24, (uint32_t)isr24, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(25, (uint32_t)isr25, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(26, (uint32_t)isr26, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(27, (uint32_t)isr27, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(28, (uint32_t)isr28, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(29, (uint32_t)isr29, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(30, (uint32_t)isr30, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(31, (uint32_t)isr31, GDT_CODE_SEGMENT, IDT_FLAGS);

    SET_IDT_GATE(32, (uint32_t)irq0, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(33, (uint32_t)irq1, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(34, (uint32_t)irq2, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(35, (uint32_t)irq3, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(36, (uint32_t)irq4, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(37, (uint32_t)irq5, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(38, (uint32_t)irq6, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(39, (uint32_t)irq7, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(40, (uint32_t)irq8, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(41, (uint32_t)irq9, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(42, (uint32_t)irq10, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(43, (uint32_t)irq11, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(44, (uint32_t)irq12, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(45, (uint32_t)irq13, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(46, (uint32_t)irq14, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(47, (uint32_t)irq15, GDT_CODE_SEGMENT, IDT_FLAGS);

    SET_IDT_GATE(128, (uint32_t)isr128, GDT_CODE_SEGMENT, IDT_FLAGS);
    SET_IDT_GATE(177, (uint32_t)isr177, GDT_CODE_SEGMENT, IDT_FLAGS);

    terminal_writestring("Loading IDT...\n");
    IDT_FLUSH_AND_LOAD((uint32_t)&idt_ptr);

    terminal_writestring("IDT Initialized and Loaded...\n");
}
void SET_IDT_GATE(uint8_t entry_num, uint32_t base, uint16_t sel, uint8_t flags)
{

    idt_entries[entry_num].base_low = base & 0xFFFF;
    idt_entries[entry_num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[entry_num].selector = sel;
    idt_entries[entry_num].zero = 0;
    idt_entries[entry_num].flags = flags | 0x60;
}

void ISR_HANDLER(struct InterruptRegisters *reg)
{
    if (reg->int_no < 32)
    {
        terminal_writestring("INTERRUPT: ");
        terminal_writestring(isr_names[reg->int_no]);
        terminal_putchar('\n');
        terminal_writestring("SYSTEM HALTED...\n");
        for (;;)
            ;
    }
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
    void (*handler)(struct InterruptRegisters *);
    handler = IRQ_ROUTINES[reg->int_no - 32];
    if (handler)
    {
        handler(reg);
    }

    if (reg->int_no >= 40)
    {
        outPort_B(PIC2, 0x20);
    }

    outPort_B(PIC1, 0x20);
}