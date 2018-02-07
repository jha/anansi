#include "anansi_com.h"

void
anansi_com_write(int port, const char *str)
{
    while (*str != 0) {
        asm volatile (
            "outb %0, %w1;"
            :
            : "a" (*str),
              "d" (port)
        );
        str++;
    }
}
