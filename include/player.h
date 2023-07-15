#include "../include/render_context.h"
#include "../include/settings.h"
#include "../include/types.h"

#include "../Vector2/Vector2.hpp"


#pragma once

class Player
{
public:
	v2 position = v2(DEFAULT_PLAYER_POS);
	f32 angle = DEFAULT_PLAYER_ANGLE;

	Player() {};

	void draw_minimap(RenderContext& ctx);
};
