#ifndef ANANSI_TRANSITION_H
#define ANANSI_TRANSITION_H

#include "types.h"

#define CR4_VMXE_ENABLE (1 << 13)

bool_t
anansi_transition_enter(void);

bool_t
anansi_transition_exit(void);

#endif /* ANANSI_TRANSITION_H */
