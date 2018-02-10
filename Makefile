obj-m := anansi.o
anansi-objs += anansi_module.o
anansi-objs += anansi_com.o
anansi-objs += anansi_msr.o
anansi-objs += anansi_hwsupp.o
anansi-objs += anansi_context.o
anansi-objs += anansi_vcore.o
anansi-objs += anansi_flags.o
anansi-objs += anansi_vmx.o
anansi-objs += anansi_transition.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

$(KBUILD_EXTMOD)/anansi_context.o: anansi_context.asm
	nasm -f elf64 $< -o $@
