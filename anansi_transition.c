#include <linux/module.h>

#include "anansi_transition.h"
#include "anansi_hwsupp.h"
#include "anansi_context.h"

bool_t
anansi_transition_enable_cr4(void)
{
    __write_cr4(__read_cr4() | CR4_VMXE_ENABLE);
    if ((__read_cr4() & CR4_VMXE_ENABLE) == 0) {
        LOG("Couldn't set VMXE in ControlRegister4");
        return FALSE;
    }

    return TRUE;
}

bool_t
anansi_transition_disable_cr4(void)
{
    __write_cr4(__read_cr4() & ~CR4_VMXE_ENABLE);
    if ((__read_cr4() & CR4_VMXE_ENABLE) != 0) {
        LOG("Couldn't unset VMXE in ControlRegister4");
        return FALSE;
    }

    return TRUE;
}

bool_t
anansi_transition_hyperjack(bool_t *success)
{
    return FALSE;
}

bool_t __attribute__((optimize ("O0")))
anansi_transition_enter(void)
{
    struct anansi_context context;
    bool_t hv_present;

    if (anansi_hwsupp() == FALSE)
        return FALSE;

    if (anansi_transition_enable_cr4() == FALSE)
        return FALSE;

    hv_present = FALSE;
    anansi_context_capture(&context);

    /* If hv_present is FALSE, then we never hypervised. After we
     * virtualize the system, we will restore all registers to our
     * captured state, EXCEPT hv_present will be set to TRUE by
     * the hypervisor. Thus, we check hv_present to detect if
     * we should virtualize or not
     *
     * This is also the reason the function is marked as O0, to
     * prevent the compiler from optimizing this branch away */
    if (hv_present == FALSE)
        anansi_transition_hyperjack(&hv_present);

    return TRUE;
}

bool_t
anansi_transition_unhyperjack(void)
{
    return FALSE;
}

bool_t
anansi_transition_exit(void)
{
    if (anansi_transition_disable_cr4() == FALSE)
        return FALSE;

    return TRUE;
}
