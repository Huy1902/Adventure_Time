#pragma once

#include "Tileset.h"

#include <map>

class TileSetManager
{
public:
	static TileSetManager* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new TileSetManager();
		}
		return s_pInstance;
	}
	Tileset* getTileseByID(const std::string& id)
	{
		if (mTileSetMap.find(id) == mTileSetMap.end())
		{
			return nullptr;
		}
		return mTileSetMap[id];
	}
	void 
		clearTileSetMap();

private:
	std::map<std::string, Tileset*> mTileSetMap;
	static TileSetManager* s_pInstance;

	TileSetManager();
};

