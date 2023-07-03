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

public:

	Game(RenderContext&);

	void update(f32);
	void draw();
};
