#include "anansi_msr.h"

inline uint64_t
anansi_msr_read(unsigned int msr)
{
    uint64_t ret;
    uint32_t msrh, msrl;

    asm volatile (
        "rdmsr"
        : "=d" (msrh),
          "=a" (msrl)
        : "c" (msr)
    );

    ret = msrl;
    ret |= ((uint64_t)msrh << 32);
    return ret;
}

inline void
anansi_msr_write(unsigned int msr, uint64_t value)
{
    asm volatile (
        "wrmsr"
        :
        : "c" (msr),
          "d" ((value >> 32) & 0xFFFFFFFF),
          "a" (value & 0xFFFFFFFF)
    );
}
