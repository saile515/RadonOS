#include "font.h"
#include <stdint.h>

static unsigned int terminal_width;
static unsigned int terminal_height;
static unsigned char terminal_buffer[1000];
static unsigned int terminal_buffer_index;

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
  for (unsigned int character_index = 0;
       character_index < terminal_buffer_index; character_index++) {
    char character = terminal_buffer[character_index];
    unsigned int character_x = character_index % terminal_width;
    unsigned int character_y = character_index / terminal_width;

    draw_character(character, character_x, character_y);
  }
}
