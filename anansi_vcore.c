#include <linux/slab.h>

#include "anansi_vcore.h"
#include "anansi_msr.h"

struct anansi_vcore *
anansi_vcore_init(void)
{
    struct anansi_vcore *vcore;
    uint32_t revision_id;

    /* Get VMX revision ID and sanity check it */
    revision_id = anansi_msr_read(IA32_VMX_BASIC_MSR) & IA32_VMX_BASIC_MSR_REV;
    if ((revision_id >> 31) != 0) {
        LOG("IA32_VMX_BASIC_MSR has invalid high bit");
        return NULL;
    }

    /* I think we are running as an interrupt, so we need to call kmalloc
     * with GFP_ATOMIC to prevent it from blocking. Needs more research */
    vcore = kmalloc(GFP_ATOMIC, sizeof (struct anansi_vcore));
    if (vcore == NULL) {
        LOG("Not enough kernel memory to allocate vcore data");
        return NULL;
    }
    memset(vcore, 0, sizeof (struct anansi_vcore));
    vcore->stack.layout.args.vmxon_phaddr = virt_to_phys(vcore->vmxon);
    vcore->stack.layout.args.vmcs_phaddr = virt_to_phys(vcore->vmcs);

    *((uint32_t *)vcore->vmxon) = revision_id;
    *((uint32_t *)vcore->vmcs) = revision_id;

    return vcore;
}

void
anansi_vcore_free(struct anansi_vcore *vcore)
{
    kfree(vcore);
}
