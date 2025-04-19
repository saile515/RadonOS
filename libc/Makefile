MODULE_NAME := libc

C_SOURCES := \
	src/math/log10.c \
	src/math/log2.c \
	src/math/pow.c \
	src/math/util.c \
	src/stdio/fprintf.c \
	src/stdio/fputc.c \
	src/stdio/printf.c \
	src/stdio/putchar.c \
	src/stdio/sprintf.c \
	src/stdio/stdout.c \
	src/stdio/util.c \
	src/stdlib/malloc.c \
	src/string/memchr.c \
	src/string/memcpy.c \
	src/string/memset.c \
	src/string/strchr.c \
	src/string/strlen.c \

C_FLAGS += -D__IS_LIBK
INCLUDE_DIRECTORIES := ../kernel/include

include ../make/build_module.mk
