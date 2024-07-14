#include "gdt.h"

struct GDT_Entry gdt_segs[5]; // null, kdata, kcode, udate, ucode, //task management
struct GDT_Locator gdt_ptr;

extern void GDT_FLUSH_AND_LOAD(addr_t);

void INIT_GDT()
{
    gdt_ptr.limit_ptr = ((sizeof(struct GDT_Entry) * 4) - 1);
    gdt_ptr.base_ptr = &gdt_segs;

    SET_GDT_GATE(0, 0, 0x00000000, 0x00, 0x0); // null descriptor
    SET_GDT_GATE(1, 0, 0xFFFFFFFF, 0x9A, 0xC); // kernel mode code segment
    SET_GDT_GATE(2, 0, 0xFFFFFFFF, 0x92, 0xC); // kernel mode data segment
    SET_GDT_GATE(3, 0, 0xFFFFFFFF, 0xFA, 0XC); // user mode code segment
    SET_GDT_GATE(4, 0, 0xFFFFFFFF, 0xF2, 0XC); // user mode code segment
    // TODO: Setup TASK MANAGEMENT

    GDT_FLUSH_AND_LOAD(&gdt_ptr);
}

void SET_GDT_GATE(uint32_t entry_num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    gdt_segs[entry_num].base_low = base & 0xFFFF;
    gdt_segs[entry_num].base_middle = (base >> 16) & 0xFF;
    gdt_segs[entry_num].base_high = (base >> 24) & 0xFF;

    gdt_segs[entry_num].limit = limit & 0XFFFF;

    gdt_segs[entry_num].flags_and_limit_high = (limit >> 16) & 0x0F;
    gdt_segs[entry_num].flags_and_limit_high = granularity & 0xF0;

    gdt_segs[entry_num].access = access;
}
