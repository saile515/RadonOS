BUILD_DIR := $(shell pwd)/build
OBJECT_DIR := $(BUILD_DIR)/objects
C_FLAGS := -std=gnu99 -ffreestanding -O2 -Wall -Wextra
C_COMPILER := i686-elf-gcc
ASSEMBLER := i686-elf-as
LINKER := i686-elf-ld

export BUILD_DIR OBJECT_DIR C_FLAGS C_COMPILER ASSEMBLER LINKER

$(shell rm -r $(BUILD_DIR))
$(shell mkdir -p $(BUILD_DIR))
$(shell mkdir -p $(OBJECT_DIR))

$(BUILD_DIR)/radonos.iso: $(BUILD_DIR)/radonos.bin
	mkdir -p $(BUILD_DIR)/iso/boot/grub
	cp $(BUILD_DIR)/radonos.bin $(BUILD_DIR)/iso/boot
	cp grub.cfg $(BUILD_DIR)/iso/boot/grub
	grub2-mkrescue -o $(BUILD_DIR)/radonos.iso $(BUILD_DIR)/iso

$(BUILD_DIR)/radonos.bin: $(OBJECT_DIR)/kernel.o
	$(C_COMPILER) -T linker.ld -o $@ -ffreestanding -O2 -nostdlib -lgcc $^

$(OBJECT_DIR)/kernel.o:
	make -C kernel

#libc.o:
#	make -C libc
