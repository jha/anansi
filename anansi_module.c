#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/smp.h>

#include "types.h"
#include "anansi_transition.h"

int __init
anansi_init(void)
{
    LOG("initializing...");

#if 1 /* Run on first CPU only */
    smp_call_function_single(0, anansi_transition_enter, NULL, 1);
#else /* Run on all CPUs */
    on_each_cpu(anansi_transition_enter, NULL, 1);
#endif

    LOG("Finished!");
    return MODULE_EXIT_SUCCESS;
}

void __exit
anansi_exit(void)
{
    LOG("unloading...");

#if 1 /* Run on first CPU only */
    smp_call_function_single(0, anansi_transition_exit, NULL, 1);
#else /* Run on all CPUs */
    on_each_cpu(anansi_transition_exit, NULL, 1);
#endif

    LOG("Finished!");
}

module_init(anansi_init);
module_exit(anansi_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("github:jha");
MODULE_DESCRIPTION("Anansi Hypervisor");
