#ifndef ANANSI_FLAGS_H
#define ANANSI_FLAGS_H

#include <linux/module.h>

/* Original x86 FLAGS */
#define X86_FLAG_CF     (1 << 0)
#define X86_FLAG_PF     (1 << 2)
#define X86_FLAG_AF     (1 << 4)
#define X86_FLAG_ZF     (1 << 6)
#define X86_FLAG_SF     (1 << 7)
#define X86_FLAG_TF     (1 << 8)
#define X86_FLAG_IF     (1 << 9)
#define X86_FLAG_DF     (1 << 10)
#define X86_FLAG_OF     (1 << 11)
#define X86_FLAG_IOPL   0x3000
#define X86_FLAG_NT     (1 << 14)

/* Extended x86 EFLAGS */
#define X86_FLAG_RF     (1 << 16)
#define X86_FLAG_VM     (1 << 17)
#define X86_FLAG_AC     (1 << 18)
#define X86_FLAG_VIF    (1 << 19)
#define X86_FLAG_VIP    (1 << 20)
#define X86_FLAG_ID     (1 << 21)

uint32_t
anansi_flags(void);

#endif /* ANANSI_FLAGS_H */
