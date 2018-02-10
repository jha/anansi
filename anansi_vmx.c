#include <linux/module.h>

#include "anansi_vmx.h"
#include "anansi_flags.h"

bool_t
anansi_vmx_vmxon(uint64_t vmxon_phaddr)
{
    asm volatile (
        "vmxon %[vmxon]"
        :
        : [vmxon] "m" (vmxon_phaddr)
    );

    if ((anansi_flags() & X86_FLAG_CF) != 0) {
        LOG("VMXON failure");
        return FALSE;
    }

    return TRUE;
}

inline void
anansi_vmx_vmxoff(void)
{
    asm volatile ("vmxoff");
}
