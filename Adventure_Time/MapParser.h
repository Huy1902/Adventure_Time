#pragma once

#include "ObjectParser.h"
#include "Map.h"

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

	MapParser() {};
	~MapParser() {};

};

