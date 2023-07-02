#include "game_core.h"
#include "draw.h"

Game::Game(RenderContext& _rc) :rc(_rc){ };

void Game::update(f32 deltaTime) {

}

void Game::draw()
{
	Surface draw_surface = rc.getSurface();


	draw_line(draw_surface, 0, 0, SCREEN_WIDTH-1, SCREEN_HEIGHT-1, 0xFFFFFFFF);
	return;

	
}
