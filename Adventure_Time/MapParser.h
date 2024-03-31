#pragma once

#include "ObjectParser.h"
#include "Map.h"
#include "EnemyObject.h"
#include "InteractObject.h"

class MapParser
{
public:
	static MapParser* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new MapParser();
		}
		return s_pInstance;
	}

	Map* parseMap(const std::string& filePath);
private:
	static MapParser* s_pInstance;

	Tileset* loadTileSet(XmlNode * tileset);

	void loadLayer(XmlNode* layers, std::vector<Layer*>& mLayer, Tileset* tileset);
	void loadEnemy(XmlNode* enemies, std::vector<EnemyObject*>& mEnemies);
	void loadSavePoint(XmlNode* save_points, std::vector<InteractObject*>& mSavePoint);

	MapParser() {};
	~MapParser() {};

};

