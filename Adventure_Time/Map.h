#ifndef MAP_H_
#define MAP_H_

#include "Tileset.h"
#include "Layer.h"

#include "PlayerObject.h"
#include "GameVector.h"

class Map
{
public:
	Map();
	void loadMap(const std::string& fileMap, const std::string& tileSetID);

	void updateMap();
	void renderMap();

	void setPlayer(PlayerObject* obj)
	{
		mPlayer = obj;
	}

private:
	std::vector<Layer*> mLayer;
	Tileset* mTileSet;

	PlayerObject* mPlayer;

	GameVector* mPosition;
};

#endif
