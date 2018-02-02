#include <linux/module.h>

#include "anansi_transition.h"
#include "anansi_hwsupp.h"

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

bool_t
anansi_transition_enter(void)
{
    bool_t hv_present;

    if (anansi_hwsupp() == FALSE)
        return FALSE;

    if (anansi_transition_enable_cr4() == FALSE)
        return FALSE;

    anansi_transition_hyperjack(&hv_present);
    if (hv_present == FALSE) {
        anansi_transition_disable_cr4();
        return FALSE;
    }

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
