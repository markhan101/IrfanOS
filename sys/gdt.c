#include "include/gdt.h"

struct GDT_Entry gdt_segs[3]; // null, kdata, kcode, udate, ucode, //task management
struct GDT_Locator gdt_ptr;

static inline void GDT_FLUSH_AND_LOAD()
{
    gdt_ptr.limit_ptr = ((sizeof(struct GDT_Entry) * 3) - 1);
    gdt_ptr.base_ptr = (uint32_t)&gdt_segs;
    asm volatile("lgdt %0" : : "m"(gdt_ptr) : "memory");
    asm volatile("mov $0x10, %%ax; \
                  mov %%ax, %%ds; \
                  mov %%ax, %%es; \
                  mov %%ax, %%fs; \
                  mov %%ax, %%gs; \
                  ljmp $0x08, $next; \
                  next:" : : : "eax");
}

void GDT_INIT()
{

    SET_GDT_GATE(0, 0, 0, 0, 0);                // null descriptor
    SET_GDT_GATE(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // kernel mode code segment
    SET_GDT_GATE(2, 0, 0xFFFFFFFF, 0x92, 0xC);  // kernel mode data segment

    // TODO: Setup TASK MANAGEMENT

    GDT_FLUSH_AND_LOAD();
}

void SET_GDT_GATE(uint32_t entry_num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    gdt_segs[entry_num].base_low = base & 0xFFFF;
    gdt_segs[entry_num].base_middle = (base >> 16) & 0xFF;
    gdt_segs[entry_num].base_high = (base >> 24) & 0xFF;

    gdt_segs[entry_num].limit = (limit & 0XFFFF);

    gdt_segs[entry_num].granularity = ((limit >> 16) & 0x0F);
    gdt_segs[entry_num].granularity |= (granularity & 0xF0);
    gdt_segs[entry_num].access = access;
}
