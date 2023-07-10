#include <string>
#include <vector>
#include <tuple>

#include "player.h"
#include "types.h"
#include "vector2.h"
#include "render_context.h"
#include "math.h"

#pragma once

struct Wall
{
	v2 a, b;
	u32 color;
	
	Wall(f32 _a, f32 _b, f32 _c, f32 _d, u32 _e) : a(_a, _b), b(_c, _d), color(_e) {};
};

class Map
{
public:
	std::vector<Wall> walls = {};
	Map(std::string path = "./map.data");

	void load_map_from_file(std::string path);
	void draw_minimap(Surface& surf);



};