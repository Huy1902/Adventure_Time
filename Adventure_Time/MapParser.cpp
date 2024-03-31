#include <iostream>

#include "MapParser.h"
#include "ObjectParser.h"
#include "GeneratorManager.h"

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
	newMap->initGround();

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

	XmlNode* save_point = nullptr;
	for (XmlNode* ite : root->child)
	{
		if (ite->element == string("objectgroup"))
		{
			string type;
			ite->takeAttribute("name", &type);
			if (type == "SavePoint")
			{
				save_point = ite;

			}
		}
	}
	vector<InteractObject*> mSavePoint;
	loadSavePoint(save_point, mSavePoint);
	newMap->setSavePoint(mSavePoint);

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

void MapParser::loadSavePoint(XmlNode* save_points, std::vector<InteractObject*>& mSavePoint)
{
	for (XmlNode* ite : save_points->child)
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
			mSavePoint.push_back(obj);
		}
	}
}