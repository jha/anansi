#ifndef ANANSI_MSR_H
#define ANANSI_MSR_H

#include <linux/module.h>

#include "types.h"

#define IA32_FTR_CTRL_MSR           0x3A
#define IA32_FTR_CTRL_MSR_LOCK      (1 << 0)
#define IA32_FTR_CTRL_MSR_VMXSMX    (1 << 1)
#define IA32_FTR_CTRL_MSR_VMXOSMX   (1 << 2)

inline uint64_t
anansi_msr_read(unsigned int msr);

inline void
anansi_msr_write(unsigned int msr, uint64_t value);

#endif /* ANANSI_MSR_H */
