
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

	f32 ray_angle = player.angle + HALF_FOV + 0.0001f;

	for (u16 _ray = 0; _ray < NUM_RAYS; _ray++)
	{
		f32 sin_a = sinf(ray_angle);
		f32 cos_a = cosf(ray_angle);
	
		// get closest wall
		Wall* closest_wall = nullptr;
		f32 min_distance = INFINITY;

		// coords of intersectiokn points
		f32 _x, _y;

		// find the wall
		for (Wall& wall : map.walls)
		{	
			// RAY in parametric: Point + Direction*T1
			f32& r_px = player.position.x;
			f32& r_py = player.position.y;
			f32 r_dx = cos_a * MAX_DEPH;
			f32 r_dy = sin_a * MAX_DEPH;

			// SEGMENT in parametric: Point + Direction*T2
			f32& s_px = wall.a.x;
			f32& s_py = wall.a.y;
			f32 s_dx = wall.b.x - wall.a.x;
			f32 s_dy = wall.b.y - wall.a.y;

			// Are they parallel? If so, no intersect
			f32 r_mag = sqrtf(r_dx * r_dx + r_dy * r_dy);
			f32 s_mag = sqrtf(s_dx * s_dx + s_dy * s_dy);

			// directions are the same - rays wont hit
			if (r_dx / r_mag == s_dx / s_mag && r_dy / r_mag == s_dy / s_mag) 
				continue;
			

			// SOLVE FOR T1 & T2
			// r_px+r_dx*T1 = s_px+s_dx*T2 && r_py+r_dy*T1 = s_py+s_dy*T2
			// ==> T1 = (s_px+s_dx*T2-r_px)/r_dx = (s_py+s_dy*T2-r_py)/r_dy
			// ==> s_px*r_dy + s_dx*T2*r_dy - r_px*r_dy = s_py*r_dx + s_dy*T2*r_dx - r_py*r_dx
			// ==> T2 = (r_dx*(s_py-r_py) + r_dy*(r_px-s_px))/(s_dx*r_dy - s_dy*r_dx)
			f32 T2 = (r_dx * (s_py - r_py) + r_dy * (r_px - s_px)) / (s_dx * r_dy - s_dy * r_dx);
			f32 T1 = (s_px + s_dx * T2 - r_px) / r_dx;

			// Must be within parametic whatevers for RAY/SEGMENT
			if (T1 < 0) continue;
			if (T2 < 0 || T2>1) continue;

			// POINT OF INTERSECTION

			f32 dist = T1;

			if (dist < min_distance)
			{
				closest_wall = &wall;
				min_distance = dist;

				_x = r_px + r_dx * T1;
				_y =  r_py + r_dy * T1;
			}

		}

		// if wall is not found
		if (closest_wall != nullptr)
		{

			// DEBUG: draw colision point 
			//draw_circle_filled(draw_surface, _x * MINIMAP_SCALE, _y * MINIMAP_SCALE, 2, closest_wall->color);

			//
			min_distance *= cosf(player.angle - ray_angle);

			// calculate proper projection height
			u16 proj_height = ((f32)SCREEN_DIST / (min_distance + 0.0001f));

			// clamp values
			if (proj_height >= WND_HEIGHT)
				proj_height = WND_HEIGHT - 1;

			// color intensity
			f32 intensity = 1.0f / (1.0f + powf(min_distance, 4)*0.1f);

			u32 color = closest_wall->color;
			unsigned char red = (color >> 24) & 0xFF;
			unsigned char green = (color >> 16) & 0xFF;
			unsigned char blue = (color >> 8) & 0xFF;

			red *= intensity;
			green *= intensity;
			blue *= intensity;

			color = (red << 24) | (green << 16) | (blue << 8) | (color & 0xFF);

			//  if distant to a or b point then make color black
			const f32 d = 0.10f;
			if (sqrtf((closest_wall->a.x - _x) * (closest_wall->a.x - _x) + (closest_wall->a.y - _y) * (closest_wall->a.y - _y)) < d||
				sqrtf((closest_wall->b.x - _x) * (closest_wall->b.x - _x) + (closest_wall->b.y - _y) * (closest_wall->b.y - _y)) < d)
			{
				color = 0;
			}

			// draw on the screen
			draw_rect_filled(draw_surface,
				_ray * PROJECTION_SCALE, WND_HEIGHT_HALF + proj_height/2, PROJECTION_SCALE, proj_height, color);

		}
		ray_angle -= DELTA_ANGLE;
	}


	///
	/// drawing minimap
	///
	 
	
	//map.draw_minimap(draw_surface);
	//player.draw_minimap(draw_surface);

}
