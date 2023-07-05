#include "render_context.h"

#include "types.h"
#include "vector2.h"

#include "settings.h"

#pragma once

class Player
{
public:
	v2 position = v2(DEFAULT_PLAYER_POS);
	f32 angle = DEFAULT_PLAYER_ANGLE;

	Player() {};

	void draw_minimap(Surface&);
};
