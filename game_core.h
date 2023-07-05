#include "render_context.h"
#include "map.h"
#include "player.h"

#include "types.h"
#include "settings.h"


#pragma once

class Game
{
private:
	RenderContext& rc;
	Map map;

	Player player;

public:

	Game(RenderContext&);

	void update(f32, const u8*);
	void draw();
};
