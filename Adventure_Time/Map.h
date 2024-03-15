#ifndef MAP_H_
#define MAP_H_

#include "Tileset.h"
#include "Layer.h"

class Map
{
public:
	Map();
	void loadMap(const std::string& fileMap, const std::string& tileSetID);

	void updateMap();
	void renderMap();

private:
	std::vector<Layer*> mLayer;
	Tileset* mTileSet;
};

#endif
