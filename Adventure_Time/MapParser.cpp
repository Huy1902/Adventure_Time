#include <iostream>

#include "MapParser.h"
#include "ObjectParser.h"
#include "GeneratorManager.h"
#include "fstream"

#include "Portal.h"
using namespace std;

MapParser* MapParser::s_pInstance = nullptr;

struct TileInfo
{
	string filePath;
	int tileSize;
	int tileWidth;
	int tileHeight;
	string fileName;

	TileInfo(const string& filePath_, const string& fileName_, int tileSize_, int tileWidth_, int tileHeight_) :
		filePath(filePath_),
		fileName(fileName_),
		tileSize(tileSize_),
		tileWidth(tileWidth_),
		tileHeight(tileHeight_)
	{

	}
	TileInfo()
	{
	};
};

Map* MapParser::parseMap(const string& filePath)
{
	XmlTree tree;
	tree.parseXmlFile(filePath);
	XmlNode* root = tree.getRoot();
	int w, h, tile_size;
	root->takeAttribute("width", &w);
	root->takeAttribute("height", &h);
	root->takeAttribute("tilewidth", &tile_size);

	Map* newMap = new Map(w, h, tile_size);

	XmlNode* tile_set = nullptr;
	for (XmlNode* ite : root->child)
	{
		if (ite->element == string("tileset"))
		{
			tile_set = ite;
			break;
		}
	}
	Tileset* tileset = loadTileSet(tile_set);

	vector<Layer*> mLayer;
	loadLayer(root, mLayer, tileset);
	newMap->setLayer(mLayer);

	XmlNode* enemies = nullptr;
	for (XmlNode* ite : root->child)
	{
		if (ite->element == string("objectgroup"))
		{
			string type;
			ite->takeAttribute("name", &type);
			if (type == "Enemy")
			{
				enemies = ite;
				break;
			}
		}
	}
	vector<EnemyObject*> mEnemy;
	loadEnemy(enemies, mEnemy);
	newMap->setEnemy(mEnemy);

	XmlNode* interact_items = nullptr;
	for (XmlNode* ite : root->child)
	{
		if (ite->element == string("objectgroup"))
		{
			string type;
			ite->takeAttribute("name", &type);
			if (type == "InteractItem")
			{
				interact_items = ite;
				break;
			}
		}
	}
	vector<InteractObject*> mInteracts;
	loadInteractItem(interact_items, mInteracts);
	newMap->setInteract(mInteracts);

	return newMap;
}

Tileset* MapParser::loadTileSet(XmlNode* tileset)
{
	TileInfo info;
	tileset->takeAttribute("name", &info.fileName);
	tileset->takeAttribute("tilewidth", &info.tileSize);

	XmlNode* image = nullptr;
	for (XmlNode* ite : tileset->child)
	{
		if (ite->element == "image")
		{
			image = ite;
			break;
		}
	}
	image->takeAttribute("source", &info.filePath);
	image->takeAttribute("width", &info.tileWidth);
	image->takeAttribute("height", &info.tileHeight);

	Tileset* newTile = new Tileset(info.filePath, info.fileName, info.tileSize, info.tileWidth, info.tileHeight);
	return newTile;
}

void MapParser::loadLayer(XmlNode* layers, vector<Layer*>& mLayer, Tileset* tileset)
{
	if (layers == nullptr)
	{
		return;
	}
	for (XmlNode* layer : layers->child)
	{
		if (layer->element == "layer")
		{
			int w, h;
			layer->takeAttribute("width", &w);
			layer->takeAttribute("height", &h);

			XmlNode* data = nullptr;
			for (XmlNode* ite : layer->child)
			{
				if (ite->element == "data")
				{
					data = ite;
					break;
				}
			}
			string layerString;
			data->takeText(&layerString);
			layerString.erase(remove(layerString.begin(), layerString.end(), char(13)), layerString.end());
			Layer* newLayer = new Layer(layerString, h, w);
			newLayer->setTileset(tileset);
			mLayer.push_back(newLayer);
		}
	}
}

void MapParser::loadEnemy(XmlNode* enemies, vector<EnemyObject*>& mEnemies)
{
	if (enemies == nullptr)
	{
		return;
	}
	for (XmlNode* ite : enemies->child)
	{
		if (ite->element == "object")
		{
			string name;
			double x, y;
			ite->takeAttribute("name", &name);
			ite->takeAttribute("x", &x);
			ite->takeAttribute("y", &y);
			EnemyObject* obj = dynamic_cast<EnemyObject*>(GeneratorManager::getInstance()->generatorObject(name));
			obj->setPosition({ x, y });
			mEnemies.push_back(obj);
		}
	}
}

void MapParser::loadInteractItem(XmlNode* interacts, std::vector<InteractObject*>& mInteracts)
{
	if (interacts == nullptr)
	{
		return;
	}
	int k = 0;
	//ofstream fout("PortalData.txt");
	for (XmlNode* ite : interacts->child)
	{
		if (ite->element == "object")
		{
			string name;
			double x, y;
			ite->takeAttribute("name", &name);
			ite->takeAttribute("x", &x);
			ite->takeAttribute("y", &y);
			InteractObject* obj = dynamic_cast<InteractObject*>(GeneratorManager::getInstance()->generatorObject(name));
			obj->setPosition({ x, y });
			mInteracts.push_back(obj);
			++k;
			if (name == "Portal")
			{
				int from = -1, to = -1;
				XmlNode* properties = ite->child[0];
				for (XmlNode* property : properties->child)
				{
					string name;
					property->takeAttribute("name", &name);
					if (name == "From")
					{
						property->takeAttribute("value", &from);
					}
					else
						if (name == "To")
						{
							property->takeAttribute("value", &to);
						}
				}
				obj->setFromTo(from, to);
			}
		}
	}
}
