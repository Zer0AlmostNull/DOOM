#include "render_context.h"
#include "map.h"

#include "types.h"
#include "settings.h"


#pragma once

class Game
{
private:
	RenderContext& rc;
	Map map;

	v2 player_pos = v2(DEFAULT_PLAYER_POS);
	f32 player_angle = DEFAULT_PLAYER_ANGLE;

public:

	Game(RenderContext&);

	void update(f32, const u8*);
	void draw();
};
