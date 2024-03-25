#include "Map.h"

#include <fstream>
#include <iostream>
#include <queue>

#include "TileSetManager.h"
#include "GameManager.h"
#include "CollisionManager.h"

#include "BarrerKnight.h"

#include "SoundManager.h"

#include "StatusManager.h"

const int MAP_WIDTH = 120;
const int MAP_HEIGHT = 24;
const int TILE_SIZE = 32;

const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 768;


using namespace std;

Map::Map()
{
	mPosition = new GameVector(0, 0);
	BarrerKnight* obj1 = new BarrerKnight();
	mEnemy.push_back(obj1);

	mBackGround = new Background();
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

void Map::processMapAndPlayer()
{
	if (mPosition->getX() <= 0)
	{
		mPosition->setX(0);
		if (mPlayer->getPosition()->getX() > WIN_WIDTH / 2 - 100 && mPlayer->getVelocity()->getX() > 0)
		{
			mPlayer->setPositionX(mPlayer->getPosition()->getX() - mPlayer->getVelocity()->getX());
			*mPosition += *mPlayer->getVelocity();
		}
		else if (mPlayer->getPosition()->getX() < 0)
		{
			mPlayer->setPositionX(0);
		}
	}
	else if (mPosition->getX() > 0 && mPosition->getX() < MAP_WIDTH * TILE_SIZE - WIN_WIDTH)
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
}

void Map::processEnemyAndPlayer()
{
	mPlayer->processData();
	if (mEnemy.empty() == true)
	{
		m_bFight = false;
	}
	else
	{
		vector<EnemyObject*>::iterator ite = mEnemy.begin();
		while (ite != mEnemy.end())
		{
			if (CollisionManager::getInstance()->checkEnemyNearPlayer(*ite) == true)
			{
				m_bFight = true;
			}
			else
			{
				m_bFight = false;
			}
			if (CollisionManager::getInstance()->checkEnemyAttackPlayer(*ite) == true)
			{
				if (StatusManager::getInstance()->whenEnemyAttackPlayer(*ite) == true)
				{
					mPlayer->getHurt();
				}
			}
			(*ite)->processData();
			if (CollisionManager::getInstance()->checkPlayerAttackEnemy(*ite) == true)
			{
				if (StatusManager::getInstance()->whenPlayerAttackEnemy(*ite) == true)
				{
					std::cout << "Player is attack\n";
					(*ite)->getHurt();
					std::cout << (*ite)->getStatus()->HP << '\n';
					if ((*ite)->isAlive() == false)
					{
						delete* ite;
						ite = mEnemy.erase(ite);
					}
					else
					{
						++ite;
					}
				}
			}
			else
			{
				++ite;
			}
		}
	}
	if (m_bFight == true)
	{
		mCountFightTime = 50;
		if (m_bIsPlayingFight == false)
		{
			Mix_HaltMusic();
			SoundManager::getInstance()->playMusic("fight_theme", -1);
			m_bIsPlayingFight = true;
		}
	}
	else
	{
		if (mCountFightTime > 0)
		{
			--mCountFightTime;
		}
		else if (mCountFightTime == 0)
		{
			Mix_HaltMusic();
			SoundManager::getInstance()->playMusic("play_theme", -1);
			m_bIsPlayingFight = false;
			--mCountFightTime;
		}
	}
}


void Map::updateMap()
{

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

	processEnemyAndPlayer();
	processMapAndPlayer();

	for (Layer* ite : mLayer)
	{
		//ite->setVelocity(*mPlayer->getVelocity());
		ite->setPosition(*mPosition);
		ite->updateLayer();
	}
	mBackGround->updateBackground();
}

void Map::renderMap()
{
	mBackGround->drawBackground();
	for (Layer* ite : mLayer)
	{
		ite->renderLayer();
	}
	for (size_t i = 0; i < mEnemy.size(); ++i)
	{
		//std::cout << mEnemy[i]->getPosition()->getX() << ' ' << mPosition->getX() << ' ' << mEnemy[i]->getPosition()->getX() << ' ' << mPosition->getX() + WIN_WIDTH << '\n';
		if (mEnemy[i]->getPosition()->getX() > mPosition->getX() && mEnemy[i]->getPosition()->getX() < mPosition->getX() + WIN_WIDTH)
		{
			mEnemy[i]->setMapPosition(*mPosition);
			mEnemy[i]->renderObject();
		}
	}
	mPlayer->renderObject();
}