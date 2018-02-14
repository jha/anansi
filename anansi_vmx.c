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

    /* 31.5 VMM SETUP & TEARDOWN
     * Check succesful execution of VMXON by checking if RFLAGS.CF = 0
     * and RFLAGS.ZF = 0 */
    if ((anansi_flags() & X86_FLAG_CF) != 0
        || (anansi_flags() & X86_FLAG_ZF) != 0)
    {
        LOG("VMXON failure");
        return FALSE;
    }

    return TRUE;
}

bool_t
anansi_vmx_vmxoff(void)
{
    asm volatile ("vmxoff");

    /* 31.5 VMM SETUP & TEARDOWN
     * When executing VMXOFF, verify succesful execution by checking if
     * RFLAGS.CF = 0 and RFLAGS.ZF = 0 */
    if ((anansi_flags() & X86_FLAG_CF) != 0
        || (anansi_flags() & X86_FLAG_ZF) != 0)
    {
        LOG("VMXOFF failure");
        return FALSE;
    }

    return TRUE;
}
