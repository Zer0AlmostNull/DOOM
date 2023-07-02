#include "draw.h"
#include <algorithm>
#include <math.h>

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
