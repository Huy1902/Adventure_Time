#include "MapManager.h"
#include "MapParser.h"

MapManager* MapManager::s_pInstance = nullptr;

bool MapManager::nextMap()
{
	if (mCurrentMap != mMap.size() - 1)
	{
		mMap[mCurrentMap + 1]->setPlayer(mMap[mCurrentMap]->getPlayer());
		++mCurrentMap;
		mMap[mCurrentMap]->getPlayer()->setPosition({0, 0});
		mMap[mCurrentMap]->initGround();
		return true;
	}
	return false;
}

bool MapManager::previousMap()
{
	if (mCurrentMap != 0)
	{
		--mCurrentMap;
		mMap[mCurrentMap]->getPlayer()->setPosition({1000, 0});
		mMap[mCurrentMap]->initGround();
		return true;
	}
	return false;
}

bool MapManager::beginFirstMap()
{
	mCurrentMap = 0;
	mMap[mCurrentMap]->initGround();
	return true;
}

MapManager::MapManager()
{
	Map* temp1 = MapParser::getInstance()->parseMap("map1.tmx");
	Map* temp2 = MapParser::getInstance()->parseMap("map2.tmx");
	mMap.push_back(temp1);
	mMap.push_back(temp2);
}

MapManager::~MapManager()
{
	for (int i = 0; i < mMap.size(); ++i)
	{
		delete mMap[i];
	}
	mMap.clear();
}


