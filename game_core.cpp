
#include "game_core.h"
#include "draw.h"
#include "math.h"

#include "SDL2/include/SDL_events.h"

Game::Game(RenderContext& _rc) :rc(_rc) { }

void Game::update(f32 deltaTime, const u8* keystate)
{

	// ----- handle input -----
	if (keystate[SDL_SCANCODE_LEFT])
		player.angle += PLATER_ROTATION_SPEED * deltaTime;
	if (keystate[SDL_SCANCODE_RIGHT]) 
		player.angle -= PLATER_ROTATION_SPEED * deltaTime;

	// make angle in range of (0, TAU>
	if (player.angle < 0)
		player.angle += TAU;
	else if (player.angle > TAU)
		player.angle -= TAU;
	
	f32 dx = 0, dy = 0,
		distance = PLAYER_SPEED * deltaTime;
	
	if (keystate[SDL_SCANCODE_D])
	{
		dx += distance * sinf(player.angle);
		dy -= distance * cosf(player.angle);
	}
	if (keystate[SDL_SCANCODE_A])
	{
		dx -= distance * sinf(player.angle);
		dy += distance * cosf(player.angle);
	}
	if (keystate[SDL_SCANCODE_W])
	{
		dx += distance * cosf(player.angle);
		dy += distance * sinf(player.angle);
	}
	if (keystate[SDL_SCANCODE_S])
	{
		dx -= distance * cosf(player.angle);
		dy -= distance * sinf(player.angle);
	}

	player.position.x += dx;
	player.position.y += dy;
}

void Game::draw()
{
	Surface draw_surface = rc.getSurface();

	f32 ray_angle = player.angle - HALF_FOV + 0.0001f;

	for (u16 _ray = 0; _ray < NUM_RAYS; _ray++)
	{
	
		f32 sin_a = sinf(ray_angle);
		f32 cos_a = cosf(ray_angle);

		f32 line_x = MINIMAP_SCALE * (player.position.x + cos_a * 2);
		f32 line_y = MINIMAP_SCALE * (player.position.y + sin_a * 2);

		line_x = min(max(.0f, line_x), (f32)WND_WIDTH - 1);
		line_y = min(max(.0f, line_y), (f32)WND_HEIGHT - 1);

		draw_line(draw_surface, player.position.x * MINIMAP_SCALE, player.position.y * MINIMAP_SCALE, line_x, line_y, 0xFF000000);
		
		ray_angle += DELTA_ANGLE;
	}


	///
	/// drawing minimap
	///
	 

	
	for (u16 wall_id = 0; wall_id < size(map.walls); wall_id++)
	{
		Wall& curr_wall = map.walls[wall_id];

		//draw_line(draw_surface, player.position.x * MINIMAP_SCALE, player.position.y * MINIMAP_SCALE,
		//		curr_wall.a.x * MINIMAP_SCALE, curr_wall.a.y *MINIMAP_SCALE, curr_wall.color);
		
		//draw_line(draw_surface, player.position.x * MINIMAP_SCALE, player.position.y * MINIMAP_SCALE,
		//	curr_wall.b.x * MINIMAP_SCALE, curr_wall.b.y * MINIMAP_SCALE, curr_wall.color);
	}
	
	map.draw_minimap(draw_surface);
	player.draw_minimap(draw_surface);

}
