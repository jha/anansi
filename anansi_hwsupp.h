#ifndef ANANSI_HWSUPP_H
#define ANANSI_HWSUPP_H

#include "types.h"

#define CPUID_GET_VENDOR    0
#define CPUID_PROC_INFO     1

/* Check against %ecx */
#define CPUID_PROC_INFO_VMX (1 << 5)

bool_t
anansi_hwsupp(void);

#endif /* ANANSI_HWSUPP_H */
