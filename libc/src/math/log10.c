#include "math.h"
#include "util.h"
#include <stdint.h>

static union int_float log10constant = {0x3e9a33cd};

double log10(double x) { return fyl2x(x, log10constant.f); }
