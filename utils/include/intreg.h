#ifndef INTREG_H
#define INTREG_H

#include <stdint.h>

struct InterruptRegisters
{
    uint32_t cr2;
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
};

#endif // INTREG_H