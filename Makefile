obj-m := anansi.o
anansi-objs += anansi_module.o
anansi-objs += anansi_msr.o
anansi-objs += anansi_hwsupp.o
anansi-objs += anansi_transition.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
