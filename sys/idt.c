#include "include/idt.h"

__attribute__((aligned(0x10))) static IDT_Entry IDT[IDT_SIZE];

static IDT_Locator IDT_ptr;

__attribute__((noreturn)) void EXCEPTION_HANDLER(char *msg)
{
    __asm__ volatile("cli");
    write_serial("EXCEPTION: ");
    write_serial(msg);
    write_serial("\n");
    __asm__ volatile("hlt");
}
void IDT_SET_DESCRIPTOR(uint8_t vector, void *isr, uint8_t flags)
{

    IDT[vector].base_low = (uint32_t)isr & 0xFFFF;
    IDT[vector].selector = GDT_CODE_SEGMENT;
    IDT[vector].zero = 0;
    IDT[vector].flags = flags;
    IDT[vector].base_high = (uint32_t)isr >> 16;
}

static bool vectors[IDT_SIZE] = {false};

extern void *isr_stub_table[];

void INIT_IDT()
{
    IDT_ptr.base_ptr = (uintptr_t)&IDT[0];
    IDT_ptr.limit = (uint16_t)sizeof(IDT_Entry) * IDT_SIZE - 1;

    for (uint8_t vector = 0; vector < 32; vector++)
    {
        IDT_SET_DESCRIPTOR(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }

    write_serial("IDT: Initialized ISR stubs...\n");

    __asm__ volatile("lidt %0" : : "m"(IDT_ptr)); // load the new IDT
    __asm__ volatile("sti");                      // set the interrupt flag
    PIC_REMAP(PIC1, PIC2);

    write_serial("Remapped PIC...\n");
}

// PIC

/*
arguments:
    offset1 - vector offset for master PIC
        vectors on the master become offset1..offset1+7
    offset2 - same for slave PIC: offset2..offset2+7
*/
void PIC_REMAP(int offset1, int offset2)
{
    uint8_t a1, a2;

    a1 = inPort_B(PIC1_DATA); // save masks
    a2 = inPort_B(PIC2_DATA);

    outPort_B(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); // starts the initialization sequence (in cascade mode)
    io_Wait();
    outPort_B(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_Wait();
    outPort_B(PIC1_DATA, offset1); // ICW2: Master PIC vector offset
    io_Wait();
    outPort_B(PIC2_DATA, offset2); // ICW2: Slave PIC vector offset
    io_Wait();
    outPort_B(PIC1_DATA, 4); // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
    io_Wait();
    outPort_B(PIC2_DATA, 2); // ICW3: tell Slave PIC its cascade identity (0000 0010)
    io_Wait();

    outPort_B(PIC1_DATA, ICW4_8086); // ICW4: have the PICs use 8086 mode (and not 8080 mode)
    io_Wait();
    outPort_B(PIC2_DATA, ICW4_8086);
    io_Wait();

    outPort_B(PIC1_DATA, a1); // restore saved masks.
    outPort_B(PIC2_DATA, a2);
}

void PIC_DISABLE()
{
    outPort_B(PIC1_DATA, 0xff);
    outPort_B(PIC2_DATA, 0xff);
}

void IRQ_SET_MASK(uint8_t IRQline)
{
    uint16_t port;
    uint8_t value;

    if (IRQline < 8)
    {
        port = PIC1_DATA;
    }
    else
    {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inPort_B(port) | (1 << IRQline);
    outPort_B(port, value);
}

void IRQ_CLEAR_MASK(uint8_t IRQline)
{
    uint16_t port;
    uint8_t value;

    if (IRQline < 8)
    {
        port = PIC1_DATA;
    }
    else
    {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = inPort_B(port) & ~(1 << IRQline);
    outPort_B(port, value);
}

/* Helper func */
static uint16_t __PIC_GET_IRQ_REQ(int ocw3)
{
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    outPort_B(PIC1_COMMAND, ocw3);
    outPort_B(PIC2_COMMAND, ocw3);
    return (inPort_B(PIC2_COMMAND) << 8) | inPort_B(PIC1_COMMAND);
}

/* Returns the combined value of the cascaded PICs irq request register */
uint16_t PIC_GET_IRR()
{
    return __PIC_GET_IRQ_REQ(PIC_READ_IRR);
}

/* Returns the combined value of the cascaded PICs in-service register */
uint16_t PIC_GET_ISR()
{
    return __PIC_GET_IRQ_REQ(PIC_READ_ISR);
}
