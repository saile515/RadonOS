#include "stdio.h"

static unsigned char stdout_buffer[8192];

FILE stdout_stream = {.buffer = stdout_buffer, .position = 0};
