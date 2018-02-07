#include <linux/module.h>

#include "anansi_transition.h"
#include "anansi_hwsupp.h"
#include "anansi_vcore.h"
#include "anansi_context.h"
#include "anansi_flags.h"

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
anansi_transition_hyperjack(bool_t *success, struct anansi_vcore *vcore)
{

    return FALSE;
}

void __attribute__((optimize ("O0")))
anansi_transition_enter(void *arg)
{
    struct anansi_vcore *vcore;
    bool_t hv_present;

    if (anansi_hwsupp() == FALSE)
        return;

    if (anansi_transition_enable_cr4() == FALSE)
        return;

    vcore = anansi_vcore_init();
    if (vcore == NULL) {
        anansi_transition_disable_cr4();
        return;
    }

    hv_present = FALSE;
    anansi_context_capture(&vcore->stack.layout.args.pre_launch_ctx);

    /* If hv_present is FALSE, then we never hypervised. After we
     * virtualize the system, we will restore all registers to our
     * captured state, EXCEPT hv_present will be set to TRUE by
     * the hypervisor. Thus, we check hv_present to detect if
     * we should virtualize or not
     *
     * This is also the reason the function is marked as O0, to
     * prevent the compiler from optimizing this branch away */
    if (hv_present == FALSE) {
        if (anansi_transition_hyperjack(&hv_present, vcore) == FALSE) {
            anansi_transition_disable_cr4();
            return;
        }
    }
}

bool_t
anansi_transition_unhyperjack(void)
{
    return FALSE;
}

void
anansi_transition_exit(void *arg)
{
    if (anansi_transition_disable_cr4() == FALSE)
        return;
}
