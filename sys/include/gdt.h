#ifndef GDT_H
#define GDT_H

#include <stdint.h>

struct GDT_Entry
{
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct GDT_Locator
{
    uint16_t limit_ptr;
    uint32_t base_ptr;
} __attribute__((packed));

void GDT_INIT();
void SET_GDT_GATE(uint32_t entry_num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

#endif