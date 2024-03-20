#include "Map.h"

#include <fstream>
#include <iostream>

#include "TileSetManager.h"
#include "GameManager.h"
#include "CollisionManager.h"

const int MAP_WIDTH = 120;
const int MAP_HEIGHT = 24;
const int TILE_SIZE = 32;

const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 768;


using namespace std;

Map::Map()
{
	mPosition = new GameVector(0, 0);
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
	CollisionManager::getInstance()->setGround(mLayer.back());
}

void Map::setPlayer(PlayerObject* obj)
{
	CollisionManager::getInstance()->setPlayer(obj);
	mPlayer = obj;
}


void Map::updateMap()
{
	mPlayer->processData();
	//std::cout << mPosition->getX() << '\n';
	/*if (mPosition->getX() == 0 || (mPosition->getX() + WIN_WIDTH) / TILE_SIZE >= MAP_WIDTH)
	{
		*mPosition += *mPlayer->getVelocity() / 2;
	}
	else if( (mPlayer->getPosition()->getX() > WIN_WIDTH / 2 && (mPosition->getX() + mPlayer->getVelocity()->getX() + WIN_WIDTH) / TILE_SIZE < MAP_WIDTH)
		|| (mPlayer->getPosition()->getX() < WIN_WIDTH / 2 && mPosition->getX() > 0)
		)
	{
		mPlayer->setPositionX(mPlayer->getPosition()->getX() - mPlayer->getVelocity()->getX());
		*mPosition += *mPlayer->getVelocity();
	}*/
	if (mPosition->getX() <= 0)
	{
		mPosition->setX(0);
		if (mPlayer->getPosition()->getX() > WIN_WIDTH / 2 - 100 && mPlayer->getVelocity()->getX() > 0)
		{
			mPlayer->setPositionX(mPlayer->getPosition()->getX() - mPlayer->getVelocity()->getX());
			*mPosition += *mPlayer->getVelocity();
		}
		else if(mPlayer->getPosition()->getX() < 0)
		{
			mPlayer->setPositionX(0);
		}
	}
	else if(mPosition->getX() > 0 && mPosition->getX() < MAP_WIDTH * TILE_SIZE - WIN_WIDTH)
	{
		mPlayer->setPositionX(mPlayer->getPosition()->getX() - mPlayer->getVelocity()->getX());
		*mPosition += *mPlayer->getVelocity();
	}
	else
	{
		mPosition->setX(MAP_WIDTH * TILE_SIZE - WIN_WIDTH);
		if (mPlayer->getPosition()->getX() < WIN_WIDTH / 2 && mPlayer->getVelocity()->getX() < 0)
		{
			mPlayer->setPositionX(mPlayer->getPosition()->getX() - mPlayer->getVelocity()->getX());
			*mPosition += *mPlayer->getVelocity();
		}
		else if (mPlayer->getPosition()->getX() > WIN_WIDTH)
		{
			mPlayer->setPositionX(WIN_WIDTH);
		}
	}
	mPosition->setY(0);
	for (Layer* ite : mLayer)
	{
		//ite->setVelocity(*mPlayer->getVelocity());
		ite->setPosition(*mPosition);
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