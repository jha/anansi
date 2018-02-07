#ifndef ANANSI_TRANSITION_H
#define ANANSI_TRANSITION_H

#include "types.h"

#define CR4_VMXE_ENABLE (1 << 13)

void
anansi_transition_enter(void *arg);

void
anansi_transition_exit(void *arg);

#endif /* ANANSI_TRANSITION_H */
