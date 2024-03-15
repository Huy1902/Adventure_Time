#include "Map.h"

#include <fstream>
#include <iostream>

#include "TileSetManager.h"

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
			Layer* layer = new Layer(decode_map, 24, 40, 32);
			layer->setTileset(mTileSet);
			mLayer.push_back(layer);
		}
	}
	else
	{
		cout << "Cannot open file map";
	}
}

void Map::renderMap()
{
	for (Layer* ite : mLayer)
	{
		ite->renderLayer();
	}
}