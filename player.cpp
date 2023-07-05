#include "player.h"
#include "draw.h"

void Player::draw_minimap(Surface& surf)
{
	// draw player
	draw_circle(surf, position.x * MINIMAP_SCALE, position.y * MINIMAP_SCALE, PLAYER_RADIUS * MINIMAP_SCALE, 0xFF000000);

	// draw view line
	const f32 sight_lenght = 2;
	f32 line_x = MINIMAP_SCALE * (position.x + cosf(angle) * sight_lenght);
	f32 line_y = MINIMAP_SCALE * (position.y + sinf(angle) * sight_lenght);

	//printf("%d %d", cosf(player_angle), sinf(player_angle));s
	// clamp values
	line_x = min(max(.0f, line_x), (f32)WND_WIDTH - 1);
	line_y = min(max(.0f, line_y), (f32)WND_HEIGHT - 1);
	draw_line(surf, position.x * MINIMAP_SCALE, position.y * MINIMAP_SCALE, line_x, line_y, 0xFFFF0000);
}
