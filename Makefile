SRC_DIR = src
TARGET_DIR = build
KERN_TARGET = $(TARGET_DIR)/kernel.bin
BOOTLOADER = $(SRC_DIR)/bootloader/bootloader.asm

DIRS = kernel kernel/drivers kernel/libc kernel/cpu_86
CFILES = $(foreach dir,$(DIRS),$(wildcard $(SRC_DIR)/$(dir)/*.c))
ASMFILES = $(foreach dir,$(DIRS),$(wildcard $(SRC_DIR)/$(dir)/*.asm))
CFLAGS = -ffreestanding $(foreach dir,$(DIRS),-I$(SRC_DIR)/$(dir))
COBJFILES = $(CFILES:%.c=%.o)
ASMOBJFILES = src/kernel/kernel_entry.asmo $(filter-out src/kernel/kernel_entry.asmo,$(ASMFILES:%.asm=%.asmo))

CC = i686-elf-gcc
LD = i686-elf-ld
ASM = nasm
QEMU = qemu-system-x86_64

all: $(KERN_TARGET) clean

$(KERN_TARGET): $(COBJFILES) $(ASMOBJFILES)
	$(LD) -o $@ -Ttext 0x1000 $(ASMOBJFILES) $(COBJFILES) --oformat binary
	nasm $(BOOTLOADER) -f bin -o $(TARGET_DIR)/boot_sect.bin
	cat $(TARGET_DIR)/boot_sect.bin $@ > $(TARGET_DIR)/os_image.bin

clean:
	rm $(COBJFILES)
	rm $(ASMOBJFILES)
	rm $(TARGET_DIR)/boot_sect.bin
	rm $(KERN_TARGET)

run-qemu:
	$(QEMU) -drive file=build/os_image.bin,index=0,format=raw,if=floppy
	
$(COBJFILES): %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(ASMOBJFILES): %.asmo : %.asm
	$(ASM) $< -f elf -o $@