#include "terminal.h"

#include "font.h"
#include "framebuffer.h"
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define terminal_buffer_size 10000

static unsigned int terminal_width;
static unsigned int terminal_height;
// TODO: Make buffer size of terminal.
static char terminal_buffer[terminal_buffer_size];
static size_t terminal_buffer_index;
static unsigned int terminal_column = 0;
static unsigned int terminal_row = 0;

void terminal_init(unsigned int width, unsigned int height) {
  terminal_width = width;
  terminal_height = height;
  terminal_buffer_index = 0;
}

void terminal_putchar(char character) {
  terminal_buffer[terminal_buffer_index++] = character;
  terminal_column++;

  if (terminal_column >= terminal_width || character == '\n') {
    terminal_column = 0;
    terminal_row++;
  }

  if (terminal_row >= terminal_height) {
    const char *first_line_end =
        memchr(terminal_buffer, '\n', terminal_buffer_size) + 1;

    size_t first_line_length =
        first_line_end == NULL
            ? terminal_width
            : (unsigned long)first_line_end - (unsigned long)terminal_buffer;

    if (first_line_length > terminal_width) {
      first_line_length = terminal_width + 1;
    }

    memcpy(terminal_buffer, terminal_buffer + first_line_length,
           terminal_buffer_size - first_line_length);
    terminal_buffer_index -= first_line_length;
    terminal_row = terminal_height - 1;
  }
}

void terminal_write(const char *string) {
  unsigned int i = 0;

  while (string[i] != '\0') {
    terminal_putchar(string[i]);
    i++;
  }
}

void terminal_render() {
  framebuffer_clear();

  unsigned int column = 0;
  unsigned int row = 0;

  for (size_t character_index = 0; character_index < terminal_buffer_index;
       character_index++) {
    char character = terminal_buffer[character_index];

    if (column >= terminal_width || character == '\n') {
      row++;
      column = 0;
      continue;
    }

    unsigned int character_x = column % terminal_width;
    unsigned int character_y = column / terminal_width + row;

    draw_character(character, character_x, character_y);

    column++;
  }
}
