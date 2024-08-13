#include "include/idt.h"

struct IDT_Entry idt_entries[IDT_SIZE];
struct IDT_Locator idt_ptr;

void IDT_FLUSH_AND_LOAD(uint32_t);

void INIT_IDT()
{

    terminal_writestring("Initializing IDT...\n");
    idt_ptr.base_ptr = (uint32_t)&idt_entries;
    idt_ptr.limit = (sizeof(struct IDT_Entry) * IDT_SIZE) - 1; // subtract 1 to get to the proper address which originally will have an offset of 1

    // set a chunk of memory
    memset(&idt_entries, sizeof(struct IDT_Entry) * IDT_SIZE, 0);

    // terminal_writestring("Loading IDT...\n");
    IDT_FLUSH_AND_LOAD((uint32_t)&idt_ptr);

    // terminal_writestring("IDT Initialized and Loaded...\n");
}
void SET_IDT_GATE(uint8_t entry_num, uint32_t base, uint16_t sel, uint8_t flags)
{

    idt_entries[entry_num].base_low = base & 0xFFFF;
    idt_entries[entry_num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[entry_num].selector = sel;
    idt_entries[entry_num].zero = 0;
    idt_entries[entry_num].flags = flags | 0x60;
}
