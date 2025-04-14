#include "stdio.h"

#include <stdint.h>

#ifdef __IS_LIBK
#include <kernel/terminal.h>
#endif

int fputc(int character, FILE *stream) {
    stream->buffer[stream->position++] = character;

#ifdef __IS_LIBK
    if (stream == stdout) {
        terminal_putchar(character);
    }
#endif

    return character;
}
