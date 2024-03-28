#include "TileSetManager.h"

#include "GameManager.h"

using namespace std;

TileSetManager* TileSetManager::s_pInstance = nullptr;


TileSetManager::TileSetManager()
{
	for (TileInfo* ite : *GameManager::getInstance()->getTileInfo())
	{
		Tileset* obj = new Tileset(ite->filePath, ite->fileName, ite->tileSize, ite->tileWidth, ite->tileHeight);
		mTileSetMap[ite->fileName] = obj;
	}
}

void TileSetManager::clearTileSetMap()
{
	for (TileInfo* ite : *GameManager::getInstance()->getTileInfo())
	{
		delete mTileSetMap[ite->fileName];
	}
	mTileSetMap.clear();
}