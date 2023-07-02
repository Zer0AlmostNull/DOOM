#include <fstream>
#include <stdexcept>

#include "map.h"

// loads map from file
void Map::load_map(std::string path)
{
	// open file
	std::ifstream file(path);
	

	// throw error
	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file: " + path);
		return;
	}

	while (!file.eof())
	{

	}

}

void Map::draw_minimap(Surface& surf)
{
	for(const Wall & wall: walls)
	{

	}
}

Map::Map(std::string path)
{
	load_map(path);
}
