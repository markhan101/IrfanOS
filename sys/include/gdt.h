#ifndef GDT_H
#define GDT_H

#include <stdint.h>

/*
The GDT (Global Descriptor Table is used to switch the kwernel to protected mode. This is crucial to handle different operations which
should be limited to the OS.
*/

/*
The GDT consists of Descriptors which are essentially used to describe the properties of a segment using a list.
THere are 3 memory models to implement this.

1. Paging (most common in modern systems)
2. Flat Memory Model (will be implemnted in this OS)
3. Segmentation (almost obsolete in modern systems)
*/

/*
The GST in the flat memory model must consist of Data Segment Descriptor and a Code Segment Descriptor.
Using the Flat model means that we treat memory as a snigle contiguous address space i.e. a long big chunk of memory.
This means that we will assume the chuck starts from 0 and goes onto whatever.
*/

/*
Each segment descriptor will have a LIMIT (segment size) and a BASE (starting location) address to go from.
*/

struct GDT_Entry
{
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t flags_and_limit_high;
    uint8_t base_high;
} __attribute__((packed));

struct GDT_Locator
{
    uint32_t base_ptr;
    uint16_t limit_ptr;
} __attribute__((packed));

void INIT_GDT();
void SET_GDT_GATE(uint32_t entry_num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity);

#endif