#ifndef MAP_H_
#define MAP_H_

#include "Tileset.h"
#include "Layer.h"

#include "PlayerObject.h"
#include "GameVector.h"

#include "EnemyObject.h"

#include "Background.h"

class Map
{
public:
	Map();
	void loadMap(const std::string& fileMap, const std::string& tileSetID);

	void updateMap();
	void renderMap();

	void setPlayer(PlayerObject* obj);


private:
	std::vector<Layer*> mLayer;
	Tileset* mTileSet;

	PlayerObject* mPlayer;

	GameVector* mPosition;

	std::vector<EnemyObject*> mEnemy;

	Background* mBackGround;
	void processMapAndPlayer();
	void processEnemyAndPlayer();

	int mCountFightTime;
	bool m_bFight;
	bool m_bIsPlayingFight;
	int mCountTimeRenderBash = 0;
};

#endif
