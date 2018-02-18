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

bool_t
anansi_vmx_vmclear(uint64_t vmcs_phaddr)
{
    asm volatile (
        "vmclear %[vmcs]"
        :
        : [vmcs] "m" (vmcs_phaddr)
    );

    /* 31.6 PREPERATION AND LAUNCHING A VIRTUAL MACHINE
     * Verify succesful execution of VMCLEAR by checking if RFLAGS.CF = 0
     * and RFLAGS.ZF = 0 */
    if ((anansi_flags() & X86_FLAG_CF) != 0
        || (anansi_flags() & X86_FLAG_ZF) != 0)
    {
        LOG("VMCLEAR failure");
        return FALSE;
    }

    return TRUE;
}

void
anansi_vmx_vmptrld(uint64_t vmcs_phaddr)
{
    asm volatile (
        "vmptrld %[vmcs]"
        :
        : [vmcs] "m" (vmcs_phaddr)
    );
}

void
anansi_vmx_vmwrite(void)
{

}

bool_t
anansi_vmx_vmlaunch(void)
{
    asm volatile ("vmlaunch");

    /* 31.6 PREPARATION AND LAUNCHING A VIRTUAL MACHINE
     * If VMLAUNCH fails due to any consistency checks before guest-state
     * loading, RFLAGS.CF or RFLAGS.ZF will be set and the VM-instruction
     * error field will contain the error code */
    if ((anansi_flags() & X86_FLAG_CF) != 0
        || (anansi_flags() & X86_FLAG_ZF) != 0)
    {
        LOG("VMLAUNCH failure");
        return FALSE;
    }

    return TRUE;
}
