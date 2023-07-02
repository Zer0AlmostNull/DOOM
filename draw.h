#include "types.h"
#include "settings.h"
#include "render_context.h"

#pragma once

void draw_line_vertical(Surface& surf, u16 x, u16 y0, u16 y1, u32 color = 0xFFFFFFFF);
void draw_line_horizontal(Surface& surf, u16 x0, u16 x1, u16 y, u32 color = 0xFFFFFFFF);
void draw_line(Surface& surf,u16 x1, u16 y1, u16 x2, u16 y2, u32 color = 0xFFFFFFFF);

void draw_circle(Surface& surf, u16 x0, u16 y0, u16 radius, u32 color = 0xFFFFFFFF);
void draw_circle_filled(Surface& surf, u16 x0, u16 y0, u16 radius, u32 color = 0xFFFFFFFF);

void draw_rect(Surface& surf, u16 x0, u16 y0, u16 width, u16 height, u32 color = 0xFFFFFFFF);
void draw_rect_filled(Surface& surf, u16 x0, u16 y0, u16 width, u16 height, u32 color = 0xFFFFFFFF);