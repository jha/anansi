#ifndef ANANSI_VCORE_H
#define ANANSI_VCORE_H

#include <linux/module.h>

#include "types.h"
#include "anansi_vcore.h"
#include "anansi_context.h"

#define ANANSI_VCORE_STACK_SPACE    (6 * PAGE_SIZE)

struct anansi_vcore_args {
    struct anansi_context pre_launch_ctx;
    uintptr_t vmxon_phaddr;
    uintptr_t vmcs_phyaddr;
};

struct anansi_vcore_stack {
    uint8_t padding[ANANSI_VCORE_STACK_SPACE -
        sizeof (struct anansi_vcore_args)];
    struct anansi_vcore_args args;
} __attribute__((packed));

struct anansi_vcore {
    union {
        uint8_t region[ANANSI_VCORE_STACK_SPACE];
        struct anansi_vcore_stack layout;
    } __attribute__((aligned (PAGE_SIZE))) stack;
    uint8_t vmxon[PAGE_SIZE] __attribute__((aligned (PAGE_SIZE)));
    uint8_t vmcs[PAGE_SIZE] __attribute__((aligned (PAGE_SIZE)));
};

struct anansi_vcore *
anansi_vcore_init(void);

void
anansi_vcore_free(struct anansi_vcore *vcore);

#endif /* ANANSI_VCORE_H */
