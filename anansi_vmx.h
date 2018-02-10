#ifndef ANANSI_VMX_H
#define ANANSI_VMX_H

#include "types.h"

bool_t
anansi_vmx_vmxon(uint64_t vmxon_phaddr);

inline void
anansi_vmx_vmxoff(void);

#endif /* ANANSI_VMX_H */
