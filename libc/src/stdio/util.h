#pragma once

#include <stdint.h>
#include <stdio.h>

int format_int(FILE *stream, uint32_t number);
int format_hex(FILE *stream, uint32_t number);
