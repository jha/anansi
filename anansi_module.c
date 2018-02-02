#include <linux/module.h>
#include <linux/kernel.h>

#include "types.h"
#include "anansi_transition.h"

int __init
anansi_init(void)
{
    LOG("initializing...");

    if (anansi_transition_enter() == FALSE) {
        LOG("Failed to transition to virtualized state");
        return MODULE_EXIT_FAILURE;
    }

    LOG("Finished!");
    return MODULE_EXIT_SUCCESS;
}

void __exit
anansi_exit(void)
{
    if (anansi_transition_exit() == FALSE)
        LOG("Failed to take CPU out of virtualized state");
}

module_init(anansi_init);
module_exit(anansi_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("github:jha");
MODULE_DESCRIPTION("Anansi Hypervisor");
