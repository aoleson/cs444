cmd_drivers/usb/host/built-in.o :=  i586-poky-linux-ld -m elf_i386   -r -o drivers/usb/host/built-in.o drivers/usb/host/pci-quirks.o drivers/usb/host/xhci-pci.o drivers/usb/host/ehci-hcd.o drivers/usb/host/ehci-pci.o drivers/usb/host/ohci-hcd.o drivers/usb/host/ohci-pci.o drivers/usb/host/uhci-hcd.o drivers/usb/host/xhci-hcd.o 
