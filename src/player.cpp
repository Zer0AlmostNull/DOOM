#include "../include/player.h"
#include "../include/render_context.h"
#include "../SDL2/include/SDL_render.h"
#include "../include/circle.h"

void Player::draw_minimap(RenderContext& ctx)
{
	// draw player
	SDL_SetRenderDrawColor(ctx.renderer, 255, 255, 255, 255);
	SDL_RenderDrawCircle(ctx.renderer, position.x * MINIMAP_SCALE, WND_HEIGHT - position.y * MINIMAP_SCALE, PLAYER_RADIUS * MINIMAP_SCALE);

	// draw view line
	const f32 sight_lenght = 2;
	const f32 line_x = MINIMAP_SCALE * (position.x + cosf(angle) * sight_lenght);
	const f32 line_y = MINIMAP_SCALE * (position.y + sinf(angle) * sight_lenght);

	SDL_SetRenderDrawColor(ctx.renderer, 255, 255, 0, 255);
	SDL_RenderDrawLine(ctx.renderer, position.x * MINIMAP_SCALE, WND_HEIGHT - position.y * MINIMAP_SCALE, line_x, WND_HEIGHT - line_y);
}
