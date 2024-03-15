#ifndef MAP_H_
#define MAP_H_

#include "Tileset.h"
#include "Layer.h"

class Map
{
public:
private:
	std::vector<Layer*> mLayer;
	Tileset* mTileSet;

};

#endif
