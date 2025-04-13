#include "math.h"

double pow(double x, double y) {
    double result = x;

    __asm__("fyl2x\n\t"
            "fld1\n\t"
            "fld %%st(1)\n\t"
            "fprem\n\t"
            "f2xm1\n\t"
            "faddp\n\t"
            "fscale\n\t"
            "fxch %%st(1)\n\t"
            "fstp %%st"
            : "+t"(result)
            : "u"(y));

    return result;
}
