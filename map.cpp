#include <fstream>
#include <stdexcept>

#include "draw.h"
#include "map.h"
#include "settings.h"

// loads map from file
void Map::load_map_from_file(std::string path)
{
	// open file
	std::ifstream file(path);
	

	// throw error if cannot open
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file: " + path);
		return;
	}


	// read line by line
	f32 x0, y0, x1, y1;
	u32 color;
	while (!file.eof())
	{
		file >> x0 >> y0 >> x1 >> y1 >> std::hex >> color;

		// add to the list
		walls.push_back(Wall(x0, y0, x1, y1, color));
	}

	// close file
	file.close();

}

void Map::draw_minimap(Surface& surf)
{
	for(const Wall & wall: walls)
	{
		draw_line(surf, wall.a.x * MINIMAP_SCALE,
						wall.a.y * MINIMAP_SCALE,
						wall.b.x * MINIMAP_SCALE,
						wall.b.y * MINIMAP_SCALE,
									wall.color);

		//
	}
}

Map::Map(std::string path)
{
	// load from file
	load_map_from_file(path);
}
