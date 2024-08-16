#include "include/string.h"

void memset(void *arr, size_t size, uint32_t value)
{
    char *array = (char *)arr;

    for (size_t i = 0; i < size; i++)
    {
        array[i] = value;
    }
}

char *itoa(int value, char *buffer, int base)
{
    if (base != 2 && base != 8 && base != 10 && base != 16)
    {
        return "Base not supported! Try 2, 8, 10, 16";
    }

    char *index_ptr = buffer;
    char *rev_ptr = buffer;
    int temp_val;

    if (value < 0 && base == 10)
    {
        *index_ptr++ = '-';
        value = -value;
        rev_ptr++;
    }

    do
    {
        temp_val = value % base;
        value /= base;
        *index_ptr++ = (temp_val > 9) ? (temp_val - 10) + 'a' : temp_val + '0';
    } while (value);

    *index_ptr = '\0';

    index_ptr--;
    while (rev_ptr < index_ptr)
    {
        char tmp_char = *rev_ptr;
        *rev_ptr++ = *index_ptr;
        *index_ptr-- = tmp_char;
    }

    return buffer;
}
