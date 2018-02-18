#include <linux/module.h>

#include "anansi_transition.h"
#include "anansi_hwsupp.h"
#include "anansi_vcore.h"
#include "anansi_context.h"
#include "anansi_vmx.h"
#include "anansi_vmcs.h"

static struct anansi_vcore *anansi_vcore_tmp = NULL;

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

void
anansi_transition_vmcs_prepare(struct anansi_context *context)
{

}

/* 31.6 PREPARATION AND LAUNCHING A VIRTUAL MACHINE
 * The following describes the minimal steps required by the VMM to set up
 * and launch a guest VM. */
bool_t
anansi_transition_hyperjack(bool_t *success, struct anansi_vcore *vcore)
{
    if (anansi_vmx_vmxon(vcore->stack.layout.args.vmxon_phaddr) == FALSE)
        return FALSE;
    vcore->stack.layout.args.hyperjacked = TRUE;

    if (anansi_vmx_vmclear(vcore->stack.layout.args.vmcs_phaddr) == FALSE)
        return FALSE;

    anansi_vmx_vmptrld(vcore->stack.layout.args.vmcs_phaddr);
    anansi_transition_vmcs_prepare(&vcore->stack.layout.args.pre_launch_ctx);

    if (anansi_vmx_vmlaunch() == FALSE)
        return FALSE;

    /* VMWRITE list
    * VMCS_LINK_POINTER
    * VMCS_MSR_BITMAP
    * VMCS_SECONDARY_VM_EXEC_CONTROL
    * VMCS_PIN_BASED_VM_EXEC_CONTROL
    * VMCS_CPU_BASED_VM_EXEC_CONTROL
    *
    * VMCS_VM_EXIT_CONTROLS
    * VMCS_VM_ENTRY_CONTROLS
    *
    * VMCS_GUEST_CS_SELECTOR
    * VMCS_GUEST_CS_LIMIT
    * VMCS_GUEST_CS_AR_BYTES
    * VMCS_GUEST_CS_BASE
    * VMCS_HOST_CS_SELECTOR
    *
    * VMCS_GUEST_SS_SELECTOR
    * VMCS_GUEST_SS_LIMIT
    * VMCS_GUEST_SS_AR_BYTES
    * VMCS_GUEST_SS_BASE
    * VMCS_HOST_SS_SELECTOR */

    return TRUE;
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
    anansi_vcore_tmp = vcore;
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
anansi_transition_unhyperjack(struct anansi_vcore *vcore)
{
    /* Disable VMX only if it was turned on */
    if (vcore->stack.layout.args.hyperjacked == TRUE)
        anansi_vmx_vmxoff();

    return TRUE;
}

void
anansi_transition_exit(void *arg)
{
    if (anansi_vcore_tmp != NULL)
        anansi_transition_unhyperjack(anansi_vcore_tmp);

    if (anansi_transition_disable_cr4() == FALSE)
        return;
}
