#include "include/string.h"

void memset(void *arr, size_t size, uint32_t value)
{
    char *array = (char *)arr;

    for (size_t i = 0; i < size; i++)
    {
        array[i] = value;
    }
}

char *itoa(int value, char *buffer)
{
}