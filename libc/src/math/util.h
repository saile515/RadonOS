#pragma once

#include <stdint.h>

union int_float {
    uint32_t i;
    float f;
};

double fyl2x(double x, double y);
double f2xm1(double x);
double fprem(double x, double y);
