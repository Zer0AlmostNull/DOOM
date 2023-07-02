#include "draw.h"
#include <algorithm>
#include <math.h>

// Even faster function for drawing vertical line
// but y0 < y1 must be true
void draw_line_vertical(Surface& surf, u16 x, u16 y0, u16 y1, u32 color)
{
    for (int y = y0; y <= y1; y++)
    {
        surf.buff[y * surf.width + x] = color;
    }
}

void draw_line_horizontal(Surface& surf, u16 x0, u16 x1, u16 y, u32 color)
{
    for (int x = x0; x < x1; x++)
    {
        surf.buff[y * surf.width + x] = color;
    }
}

void draw_line(Surface& surf, u16 x0, u16 y0, u16 x1, u16 y1, u32 color)
{
    // check if the coordinates are out of bounds
    if (x0 >= surf.width || x1 >= surf.width || y0 >= surf.height || y1 >= surf.height)
    {
        // coordinates are out of bounds, do nothing
        return;
    }

    // Bresenham's line drawing algorithm
    bool steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep)
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = abs(y1 - y0);
    int error = dx / 2;
    int ystep = (y0 < y1) ? 1 : -1;
    int y = y0;

    for (int x = x0; x <= x1; x++) {
        if (steep) {
            surf.buff[x * surf.width + y] = color;
        }
        else {
            surf.buff[y * surf.width + x] = color;
        }
        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}

void draw_circle(Surface& surf, u16 x0, u16 y0, u16 radius, u32 color)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        surf.buff[((y0 + y) * surf.width) + (x0 + x)] = color;
        surf.buff[((y0 + x) * surf.width) + (x0 + y)] = color;
        surf.buff[((y0 - x) * surf.width) + (x0 + y)] = color;
        surf.buff[((y0 - y) * surf.width) + (x0 + x)] = color;
        surf.buff[((y0 - y) * surf.width) + (x0 - x)] = color;
        surf.buff[((y0 - x) * surf.width) + (x0 - y)] = color;
        surf.buff[((y0 + x) * surf.width) + (x0 - y)] = color;
        surf.buff[((y0 + y) * surf.width) + (x0 - x)] = color;

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }

}

void draw_circle_filled(Surface& surf, u16 x0, u16 y0, u16 radius, u32 color)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        draw_line(surf, x0 - x, y0 + y, x0 + x, y0 + y, color);
        draw_line(surf, x0 - x, y0 - y, x0 + x, y0 - y, color);
        draw_line(surf, x0 - y, y0 + x, x0 + y, y0 + x, color);
        draw_line(surf, x0 - y, y0 - x, x0 + y, y0 - x, color);

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void draw_rect(Surface& surf, u16 x0, u16 y0, u16 width, u16 height, u32 color)
{
    draw_line_horizontal(surf, x0, x0 + width, y0 ,color);
    draw_line_horizontal(surf, x0, x0 + width, y0 - height, color);

    draw_line_vertical(surf, x0, y0 - height, y0, color);
    draw_line_vertical(surf, x0 + width, y0 - height, y0 , color);
}

void draw_rect_filled(Surface& surf, u16 x0, u16 y0, u16 width, u16 height, u32 color)
{
    for (int x = x0; x < x0 + width; x++)
    {
        for (int y = y0 - height; y < y0; y++)
        {
            surf.buff[y * surf.width + x] = color;
        }
    }
}


