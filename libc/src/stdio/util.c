#include "util.h"

#include "math.h"
#include <stdio.h>

int format_int(FILE *stream, uint32_t number) {
    if (number == 0) {
        fputc('0', stream);
        return 1;
    }

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

int format_hex(FILE *stream, uint32_t number) {
    int magnitude = 0;

    {
        int number_copy = number;

        while (number_copy >>= 4) {
            number_copy &= 0x0FFFFFFF;
            ++magnitude;
        }
    }

    for (int i = magnitude; i >= 0; i--) {
        char hex_digit = (number >> (i * 4)) & 0xF;

        hex_digit += hex_digit > 9 ? 'a' - 10 : '0';

        fputc(hex_digit, stream);
    }

    return magnitude + 1;
}
