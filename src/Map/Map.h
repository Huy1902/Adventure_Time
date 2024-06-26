#ifndef MAP_H_
#define MAP_H_

#include "Tileset.h"
#include "Layer.h"

#include "PlayerObject.h"
#include "GameVector.h"

#include "EnemyObject.h"

#include "Background.h"

#include "InteractObject.h"
class Map
{
public:
	Map(int width, int height, int tileSize);

	void updateMap();
	void renderMap();

	void setPlayer(PlayerObject* obj);
	void setEnemy(const std::vector<EnemyObject*>& obj)
	{
		mEnemy = obj;
	}
	void setLayer(const std::vector<Layer*>& obj)
	{
		mLayer = obj;
	}
	void setInteract(const std::vector<InteractObject*>& interacts)
	{
		mInteractItem = interacts;
	}
	void setPosition(const GameVector& obj)
	{
		*mPosition = obj;
	}
	void initGround();
	PlayerObject* getPlayer() const
	{
		return mPlayer;
	}
	~Map();
private:
	std::vector<Layer*> mLayer;
	//Tileset* mTileSet;

	PlayerObject* mPlayer;

	GameVector* mPosition;

	std::vector<EnemyObject*> mEnemy;

	void processMapAndPlayer();
	void processEnemyAndPlayer();
	void processEnemyAndMap();
	void processInteractObjectAndPlayer();
	void processPlayerAndArrow();
	void processEnemyAndSpell();

	int mCountFightTime;
	bool m_bFight;
	bool m_bIsPlayingFight;
	int mCountTimeRenderBash = 0;

	int mMapWidth = 120;
	int mMapHeight = 24;
	int mTileSize = 32;

	GameVector mSavedMapPosition;
	GameVector mSavedPlayerPosition;
	std::vector<InteractObject*> mInteractItem;
	bool m_bSwitchMap = false;
};

#endif
