#include <SDL.h>
#include <iostream>

#include "settings.h"
#include "types.h"
#include "macros.h"

#include "render_context.h"
#include "game_core.h"



RenderContext rc;


int main(int argc, char *args[])
{
    // Init SDL
    ASSERT(!SDL_Init(SDL_INIT_EVERYTHING),
        "SDL failed to initialize: %s\n",
        SDL_GetError());

    // create window
    rc.window = SDL_CreateWindow("-", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WND_WIDTH, WND_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    ASSERT(rc.window, "Failed to initialize window: %s\n", SDL_GetError());

    // create renderer  
    rc.renderer = SDL_CreateRenderer(rc.window, -1, SDL_RENDERER_PRESENTVSYNC);
    ASSERT(rc.renderer, "Failed to initialize renderer: %s\n", SDL_GetError());

    // Create a streaming texture
    rc.texture = SDL_CreateTexture(rc.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WND_WIDTH, WND_HEIGHT);
    ASSERT(rc.texture, "Failed to initialize texture: %s\n", SDL_GetError());

    // init the game
    Game g(rc);

    // init clock/timer
    u64 now = SDL_GetPerformanceCounter();
    u64 last = 0;

    f32 deltaTime = .0001f;

    // event loop
    SDL_Event windowEvent;
    while (1)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
                break;

        }

        // ----- handle timing-----
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (f32)((now - last) * 1000 / (f32)SDL_GetPerformanceFrequency()) * 0.001f;
        //f32 fps = 1 / deltaTime;

        // ----- handle input -----
        const u8* keystate = SDL_GetKeyboardState(NULL);

        g.update(deltaTime, keystate);
        g.draw();


        SDL_UpdateTexture(rc.texture, NULL, rc.buff, WND_WIDTH * sizeof(u32));
        SDL_RenderCopyEx(
            rc.renderer,
            rc.texture,
            NULL,
            NULL,
            0.0,
            NULL,
            SDL_FLIP_VERTICAL);
        SDL_RenderPresent(rc.renderer);

        // reset the screen
        std::memset(rc.buff, 0, PIXEL_COUNT * sizeof(u32));
    }


    SDL_DestroyWindow(rc.window);
    SDL_Quit();




	return 0;
}