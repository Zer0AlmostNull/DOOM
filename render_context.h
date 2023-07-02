#include <SDL_render.h>

#include "types.h"
#include "settings.h"

#pragma once


// I stole that one from pygame
class Surface
{
private:
    bool is_container = false;
public:
    u16 width;
    u16 height;
    u32* buff;

    //
    Surface(u32* _buff, u16 _width, u16 _height) { buff = _buff; width = _width; height = _height; is_container = true; };

    Surface(u16 _width, u16 _height) : width(_width), height(_height)
    {
           buff = new u32[(u32)(_width) * (u32)(_height)];
    }

    ~Surface()
    {
        if (!is_container)
            delete[] buff;
    }
};

struct RenderContext
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;

    u32 buff[WND_WIDTH * WND_HEIGHT] = { 0 };

    Surface getSurface() { return Surface(buff, WND_WIDTH, WND_HEIGHT); };
};