#ifndef ANANSI_VMX_H
#define ANANSI_VMX_H

#include "types.h"

bool_t
anansi_vmx_vmxon(uint64_t vmxon_phaddr);

bool_t
anansi_vmx_vmxoff(void);

bool_t
anansi_vmx_vmclear(uint64_t vmcs_phaddr);

void
anansi_vmx_vmptrld(uint64_t vmcs_phaddr);

void
anansi_vmx_vmwrite(void);

bool_t
anansi_vmx_vmlaunch(void);

#endif /* ANANSI_VMX_H */
