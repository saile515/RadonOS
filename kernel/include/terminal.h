#pragma once

#include <stdint.h>

void terminal_init(unsigned int width, unsigned int height);
void terminal_putchar(char character);
void terminal_write(const char *string);
void terminal_render();
