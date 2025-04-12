#include "string.h"

// Algorithm taken from glibc
// (https://sourceware.org/git/?p=glibc.git;a=blob;f=string/memset.c).

void *memset(void *destination, int character, size_t count) {
    unsigned long destination_address = (unsigned long)destination;

    if (count >= 8) {
        long repeated_character = character;
        repeated_character |= repeated_character << 8;
        repeated_character |= repeated_character << 16;

        if (sizeof(unsigned long) > 4) {
            repeated_character |= (repeated_character << 16) << 16;
        }

        while (destination_address % sizeof(unsigned long) != 0) {
            ((unsigned char *)destination_address)[0] = character;
            destination_address++;
            count--;
        }

        unsigned int block_size = (sizeof(unsigned long) * 8);

        while (count / block_size > 0) {
            ((unsigned long *)destination_address)[0] = repeated_character;
            ((unsigned long *)destination_address)[1] = repeated_character;
            ((unsigned long *)destination_address)[2] = repeated_character;
            ((unsigned long *)destination_address)[3] = repeated_character;
            ((unsigned long *)destination_address)[4] = repeated_character;
            ((unsigned long *)destination_address)[5] = repeated_character;
            ((unsigned long *)destination_address)[6] = repeated_character;
            ((unsigned long *)destination_address)[7] = repeated_character;

            destination_address += block_size;
            count -= block_size;
        }

        count %= block_size;

        block_size = sizeof(unsigned long);

        while (count / block_size > 0) {
            ((unsigned long *)destination_address)[0] = repeated_character;
            destination_address += block_size;
            count -= block_size;
        }

        count %= block_size;
    }

    while (count > 0) {
        ((unsigned char *)destination_address)[0] = character;
        destination_address++;
        count--;
    }

    return destination;
}
