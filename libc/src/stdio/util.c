#include "util.h"

#include "math.h"

int format_int(FILE *stream, uint32_t number) {
    int magnitude = log10(number);

    uint32_t rest = number;

    for (int i = 0; i <= magnitude; ++i) {
        int multiplier = pow(10, magnitude - i);

        int digit = (rest / multiplier);

        rest -= digit * multiplier;

        fputc(digit + '0', stream);
    }

    return magnitude + 1;
}
