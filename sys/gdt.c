#include "include/gdt.h"

#define ENTRIES 3
struct GDT_Entry gdt_entries[ENTRIES]; // null, kdata, kcode, udate, ucode, //task management
struct GDT_Locator gdt_ptr;

static inline void GDT_FLUSH_AND_LOAD()
{
    gdt_ptr.limit_ptr = ((sizeof(struct GDT_Entry) * ENTRIES) - 1);
    gdt_ptr.base_ptr = (uint32_t)&gdt_entries;
    asm volatile("lgdt (%0)" : : "r"(&gdt_ptr));
    asm volatile("mov $0x10, %%ax; \
                  mov %%ax, %%ds; \
                  mov %%ax, %%es; \
                  mov %%ax, %%fs; \
                  mov %%ax, %%gs; \
                  ljmp $0x08, $next; \
                  next:" : : : "eax");
}

// extern void GDT_FLUSH_AND_LOAD(struct GDT_Locator *gdt_ptr);

void INIT_GDT()
{
    // gdt_ptr.limit_ptr = ((sizeof(struct GDT_Entry) * ENTRIES) - 1);
    // gdt_ptr.base_ptr = (uint32_t)&gdt_entries;

    SET_GDT_GATE(0, 0, 0x00000000, 0x00, 0x0);          // null descriptor
    SET_GDT_GATE(1, 0x00400000, 0x003FFFFF, 0x9A, 0xC); // kernel mode code segment
    SET_GDT_GATE(2, 0x00800000, 0x003FFFFF, 0x92, 0xC); // kernel mode data segment

    // write_serial("gate set!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");

    // SET_GDT_GATE(0, 0, 0, 0, 0);                // null descriptor
    // SET_GDT_GATE(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // kernel mode code segment
    // SET_GDT_GATE(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // kernel mode data segment
    // SET_GDT_GATE(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // user mode code segment
    // SET_GDT_GATE(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // user mode data segment

    // TODO: Setup TASK MANAGEMENT

    // GDT_FLUSH_AND_LOAD(&gdt_ptr);
    GDT_FLUSH_AND_LOAD();
}

void SET_GDT_GATE(uint32_t entry_num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
    gdt_entries[entry_num].base_low = base & 0xFFFF;
    gdt_entries[entry_num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[entry_num].base_high_gdt = (base >> 24) & 0xFF;

    gdt_entries[entry_num].limit = limit & 0XFFFF;

    gdt_entries[entry_num].flags_and_limit_high = (limit >> 16) & 0x0F;
    gdt_entries[entry_num].flags_and_limit_high = granularity & 0xF0;

    gdt_entries[entry_num].access = access;
}
