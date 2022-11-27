#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

typedef struct Color {
    uint8_t red, green, blue, alpha;
} Color;

static inline Color rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    return (Color) { red, green, blue, 0xFF };
}

static inline Color rgba(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    return (Color) { red, green, blue, alpha };
}

typedef struct Graphics {
    void (*present)(struct Graphics* graphics);
    void (*clear)(struct Graphics* graphics, Color color);
    void (*draw_rect)(struct Graphics* graphics, int x, int y, int width, int height, Color color);
} Graphics;

#endif
