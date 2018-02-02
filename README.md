Simple WIP hypervisor designed to facilitate spying on the target.

When it's finished, it will support page shadowing via EPT splitting, as well as hypervisor-assisted arbitrary read/write to physical addresses. This isn't too useful on Linux, but has broader implications for Windows. For example, many anticheat solutions detect open handles to game processes. By utilizing a hypervisor, even a driver would not be able to realize cheat software reading and writing to game memory
