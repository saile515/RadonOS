MODULE_NAME := kernel

C_SOURCES := \
  src/font.c \
  src/framebuffer.c \
  src/kernel.c \
	src/paging.c \
	src/physical_memory.c \
  src/terminal.c 

INCLUDE_DIRECTORIES := ../libc/include ./include/kernel

LOCAL_OBJECT_DIR := $(OBJECT_DIR)/$(MODULE_NAME)
OBJECTS := $(LOCAL_OBJECT_DIR)/boot.o $(LOCAL_OBJECT_DIR)/consolefont.o

include ../make/build_module.mk

$(LOCAL_OBJECT_DIR)/boot.o: src/boot.s
	$(ASSEMBLER) $^ -o $@ -g

$(LOCAL_OBJECT_DIR)/consolefont.o: consolefont.psf
	objcopy -O elf32-i386 -B i386 -I binary $^ $@
