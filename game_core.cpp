#include "game_core.h"
#include "draw.h"
#include "math.h"
#include "SDL2/include/SDL_events.h"

Game::Game(RenderContext& _rc) :rc(_rc) {}

void Game::update(f32 deltaTime, const u8* keystate)
{

	// ----- handle input -----
	if (keystate[SDL_SCANCODE_LEFT])
		player_angle += PLATER_ROTATION_SPEED * deltaTime;
	if (keystate[SDL_SCANCODE_RIGHT]) 
		player_angle -= PLATER_ROTATION_SPEED * deltaTime;

	player_angle = fmodf(player_angle, TAU);

	
	if (keystate[SDL_SCANCODE_D])
	{
		player_pos.x -= PLAYER_SPEED * deltaTime * cosf(player_angle);
		player_pos.y += PLAYER_SPEED * deltaTime * sinf(player_angle);
	}

	if (keystate[SDL_SCANCODE_A])
	{
		player_pos.x += PLAYER_SPEED * deltaTime * cosf(player_angle);
		player_pos.y -= PLAYER_SPEED * deltaTime * sinf(player_angle);
	}

	if (keystate[SDL_SCANCODE_W])
	{
		player_pos.x += PLAYER_SPEED * deltaTime * cosf(player_angle);
		player_pos.y += PLAYER_SPEED * deltaTime * sinf(player_angle);
	}
	if (keystate[SDL_SCANCODE_S])
	{
		player_pos.x -= PLAYER_SPEED * deltaTime * cosf(player_angle);
		player_pos.y -= PLAYER_SPEED * deltaTime * sinf(player_angle);
	}

}

void Game::draw()
{
	Surface draw_surface = rc.getSurface();


	// drawing minimap
	map.draw_minimap(draw_surface);

	// draw player
	draw_circle(draw_surface, player_pos.x * MINIMAP_SCALE, player_pos.y * MINIMAP_SCALE, PLAYER_RADIUS * MINIMAP_SCALE, 0xFF000000);

	// draw view line
	const f32 sight_lenght = 1;
	f32 line_x = MINIMAP_SCALE * (player_pos.x + cosf(player_angle) * sight_lenght);
	f32 line_y = MINIMAP_SCALE * (player_pos.y + sinf(player_angle) * sight_lenght);

	//printf("%d %d", cosf(player_angle), sinf(player_angle));
	// clamp values
	line_x = min(max(.0f, line_x), (f32)WND_WIDTH-1);
	line_y = min(max(.0f, line_y), (f32)WND_HEIGHT - 1);
	draw_line(draw_surface, player_pos.x * MINIMAP_SCALE, player_pos.y * MINIMAP_SCALE, line_x, line_y, 0xFFFF0000);


	f32 ray_angle = player_angle - HALF_FOV + 0.0001;

	for (u16 _ray = 0; _ray < NUM_RAYS; _ray++)
	{
	
		f32 sin_a = sinf(ray_angle);
		f32 cos_a = cosf(ray_angle);

		f32 line_x = MINIMAP_SCALE * (player_pos.x + cos_a*2);
		f32 line_y = MINIMAP_SCALE * (player_pos.y + sin_a*2);

		line_x = min(max(.0f, line_x), (f32)WND_WIDTH - 1);
		line_y = min(max(.0f, line_y), (f32)WND_HEIGHT - 1);

		draw_line(draw_surface, player_pos.x * MINIMAP_SCALE, player_pos.y * MINIMAP_SCALE, line_x, line_y, 0x00FF00FF);

		ray_angle += DELTA_ANGLE;
	}
	
	
}
