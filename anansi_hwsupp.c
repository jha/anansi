#include <linux/module.h>
#include <cpuid.h>
#include <linux/string.h>

#include "anansi_hwsupp.h"
#include "anansi_msr.h"

bool_t
anansi_hwsupp_is_intel(void)
{
    uint32_t eax;
    char vendor[12];

    /* As per leaf to get vendor ID
     * vendor is stored in %ebx, %edx, %ecx, in that order */
    if (__get_cpuid(CPUID_GET_VENDOR, &eax,
        (int *)&vendor[0], (int *)&vendor[8], (int *)&vendor[4]) == FALSE)
    {
        LOG("CPUID instruction did not execute");
        return FALSE;
    }

    if (memcmp(vendor, "GenuineIntel", 12) == 0)
        return TRUE;

    LOG("This is not an Intel CPU!");
    return FALSE;
}

bool_t
anansi_hwsupp_vmx_enabled(void)
{
    uint32_t eax, ebx, ecx, edx;

    /* Check if their processor supports it */
    __get_cpuid(CPUID_PROC_INFO, &eax, &ebx, &ecx, &edx);
    if ((ecx & CPUID_PROC_INFO_VMX) == 0) {
        LOG("Intel processor is too old to support VMX");
        return FALSE;
    }

    return TRUE;
}

bool_t
anansi_hwsupp_vmx_feature(void)
{
    uint64_t ftr_ctrl;

    /* Test if VT-x is allowed outside of SMX */
    ftr_ctrl = anansi_msr_read(IA32_FTR_CTRL_MSR);
    if ((ftr_ctrl & IA32_FTR_CTRL_MSR_VMXOSMX) == 0) {
        /* Check if we can overwrite it and allow VT-x */
        if ((ftr_ctrl & IA32_FTR_CTRL_MSR_LOCK) == 0) {
            LOG("Weird, your BIOS did not lock IA32_FEATURE_CONTROL_MSR!"
                "I am locking it behind me");
            anansi_msr_write(IA32_FTR_CTRL_MSR,
                ftr_ctrl | IA32_FTR_CTRL_MSR_LOCK | IA32_FTR_CTRL_MSR_VMXOSMX);
            return TRUE;
        }

        LOG("Your BIOS has disabled VMX outside of SMX");
        return FALSE;
    }

    return TRUE;
}

bool_t
anansi_hwsupp(void)
{
    /* Check if we are using an Intel processor */
    if (anansi_hwsupp_is_intel() == FALSE)
        return FALSE;

    /* Check that the processor supports VMX */
    if (anansi_hwsupp_vmx_enabled() == FALSE)
        return FALSE;

    /* Check that VMX is a valid feature (enabled) */
    if (anansi_hwsupp_vmx_feature() == FALSE)
        return FALSE;

    return TRUE;
}
