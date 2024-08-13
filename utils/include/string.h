#ifndef STRING_H
#define STRING_H

#include <stdint.h>
#include <stddef.h>

void memset(void *arr, size_t size, uint32_t value);
char *itoa(int value, char *buffer);

#endif