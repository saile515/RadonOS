#include "font.h"
#include <stddef.h>
#include <stdint.h>

static unsigned int terminal_width;
static unsigned int terminal_height;
static unsigned char terminal_buffer[1000];
static size_t terminal_buffer_index;

void terminal_init(unsigned int width, unsigned int height) {
  terminal_width = width;
  terminal_height = height;
  terminal_buffer_index = 0;
}

void terminal_putchar(char character) {
  terminal_buffer[terminal_buffer_index++] = character;
}

void terminal_write(const char *string) {
  unsigned int i = 0;

  while (string[i] != '\0') {
    terminal_putchar(string[i]);
    i++;
  }
}

void terminal_render() {
  unsigned int column = 0;
  unsigned int row = 0;

  for (size_t character_index = 0; character_index < terminal_buffer_index;
       character_index++) {
    char character = terminal_buffer[character_index];

    if (character == '\n') {
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
