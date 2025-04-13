#include "util.h"

double fyl2x(double x, double y) {
    double result = x;

    __asm__("fyl2x" : "+t"(result) : "u"(y));

    return result;
}

double f2xm1(double x) {
    double result = x;

    __asm__("f2xm1" : "+t"(result));

    return result;
}

double fprem(double x, double y) {
    double result = x;

    __asm__("fprem" : "+t"(result) : "u"(y));

    return result;
}
