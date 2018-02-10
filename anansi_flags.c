#include "anansi_flags.h"

uint32_t
anansi_flags(void)
{
    uint64_t flags;

    asm volatile (
        "pushfq;"
        "popq %[flags];"
        : [flags] "=r" (flags)
    );

    return flags & 0xFFFFFFFF;
}
