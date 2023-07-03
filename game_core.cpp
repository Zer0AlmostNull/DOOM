#include "game_core.h"
#include "draw.h"

Game::Game(RenderContext& _rc) :rc(_rc) {}

void Game::update(f32 deltaTime)
{

}

void Game::draw()
{
	Surface draw_surface = rc.getSurface();

	map.draw_minimap(draw_surface);
	// testing
	//draw_line(draw_surface, 0, 0, WND_WIDTH-1, WND_HEIGHT-1, 0xFFFFFFFF);
	//draw_circle_filled(draw_surface, WND_WIDTH_HALF, WND_HEIGHT_HALF, 100, 0xFF000000);
	//draw_rect(draw_surface, 0, WND_HEIGHT - 1, 200, 400, 0xFFFF00FF);
	
}
