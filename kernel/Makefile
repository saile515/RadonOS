MODULE_NAME := kernel

C_SOURCES := src/kernel.c src/terminal.c src/framebuffer.c src/font.c
INCLUDE_DIRECTORIES := ../libc/include

LOCAL_OBJECT_DIR := $(OBJECT_DIR)/$(MODULE_NAME)
OBJECTS := $(LOCAL_OBJECT_DIR)/boot.o $(LOCAL_OBJECT_DIR)/consolefont.o

include ../make/build_module.mk
	
$(LOCAL_OBJECT_DIR)/boot.o: src/boot.s
	$(ASSEMBLER) $^ -o $@

$(LOCAL_OBJECT_DIR)/consolefont.o: consolefont.psf
	objcopy -O elf32-i386 -B i386 -I binary $^ $@
