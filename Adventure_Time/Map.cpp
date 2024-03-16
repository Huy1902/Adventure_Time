#include "Map.h"

#include <fstream>
#include <iostream>

#include "TileSetManager.h"
#include "GameManager.h"

const int MAP_WIDTH = 120;
const int MAP_HEIGHT = 24;
const int TILE_SIZE = 32;


using namespace std;

Map::Map()
{

}

void Map::loadMap(const std::string& fileMap, const std::string& tileSetID)
{
	Tileset* mTileSet = TileSetManager::getInstance()->getTileseByID(tileSetID);

	ifstream fin(fileMap);

	if (fin.is_open())
	{
		string temp;
		while (fin.eof() == false)
		{
			string decode_map = "";
			while (fin >> temp)
			{
				if (temp == "/")
				{
					break;
				}
				decode_map += temp;
			}
			Layer* layer = new Layer(decode_map, MAP_HEIGHT, MAP_WIDTH, TILE_SIZE);
			layer->setTileset(mTileSet);
			mLayer.push_back(layer);
		}
	}
	else
	{
		cout << "Cannot open file map";
	}
}

void Map::updateMap()
{
	mPlayer->processData();
	mPlayer->setPositionX(mPlayer->getPosition()->getX() - mPlayer->getVelocity()->getX());
	for (Layer* ite : mLayer)
	{
		ite->setVelocityX(mPlayer->getVelocity()->getX());
		//ite->setVelocity(*mPlayer->getVelocity());
		ite->updateLayer();
	}
}

void Map::renderMap()
{
	for (Layer* ite : mLayer)
	{
		ite->renderLayer();
	}
	mPlayer->renderObject();
}