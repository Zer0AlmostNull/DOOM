#include <fstream>
#include <stdexcept>

#include "../include/map.h"
#include "../include/settings.h"

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
		// read from file
		file >> x0 >> y0 >> x1 >> y1 >> std::hex >> color;

		// add to the list
		walls.push_back(Wall(x0, y0, x1, y1, color));
	}

	// close file
	file.close();

}

void Map::draw_minimap(RenderContext& ctx)
{
	for(const Wall & wall: walls)
	{
		const unsigned char red = (wall.color >> 24) & 0xFF;
		const unsigned char green = (wall.color >> 16) & 0xFF;
		const unsigned char blue = (wall.color >> 8) & 0xFF;

		SDL_SetRenderDrawColor(ctx.renderer, red, green, blue, 255);

		SDL_RenderDrawLine(ctx.renderer, wall.a.x * MINIMAP_SCALE,
						WND_HEIGHT - wall.a.y * MINIMAP_SCALE,
						wall.b.x * MINIMAP_SCALE,
						WND_HEIGHT - wall.b.y * MINIMAP_SCALE);
	}
}

Map::Map(std::string path)
{
	// load from file
	load_map_from_file(path);

}
