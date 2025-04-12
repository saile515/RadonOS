#include "framebuffer.h"
#include <stdint.h>

extern char _binary_consolefont_psf_start;
extern char _binary_consolefont_psf_end;

#define PSF_FONT_MAGIC 0x864ab572

typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t header_size;
    uint32_t flags;
    uint32_t glyph_count;
    uint32_t glyph_size;
    uint32_t glyph_height;
    uint32_t glyph_width;
} psf_font_t;

const psf_font_t *font_header = (psf_font_t *)&_binary_consolefont_psf_start;

// TODO: Support different glyph sizes.
static const unsigned int glyph_width = 8;
static const unsigned int glyph_height = 16;

typedef const uint8_t glyph_t[16];

glyph_t *font_glyphs =
    (glyph_t *)(&_binary_consolefont_psf_start + sizeof(psf_font_t));

void draw_glyph(const glyph_t *glyph, unsigned int x, unsigned int y) {
    for (unsigned int row_index = 0; row_index < glyph_height; row_index++) {
        uint8_t row = (*glyph)[row_index];

        for (unsigned int column_index = 0; column_index < glyph_width;
             column_index++) {
            if (!(row >> (glyph_width - column_index) & 1)) {
                continue;
            }

            unsigned int x_offset = x + column_index;
            unsigned int y_offset = y + row_index;

            framebuffer[x_offset + y_offset * framebuffer_width] = 0xffffffff;
        }
    }
}

void draw_character(char character, unsigned int character_x,
                    unsigned int character_y) {
    unsigned int x = character_x * glyph_width;
    unsigned int y = character_y * glyph_height;

    glyph_t *glyph = &font_glyphs[(uint8_t)character];

    draw_glyph(glyph, x, y);
}
