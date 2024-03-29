#include "Map.h"

#include <fstream>
#include <iostream>
#include <queue>

#include "TileSetManager.h"
#include "GameManager.h"
#include "CollisionManager.h"
#include "GeneratorManager.h"
#include "SoundManager.h"
#include "StatusManager.h"
#include "FontManager.h"

#include "BarrerKnight.h"
#include "DroidZapper.h"


const int MAP_WIDTH = 120;
const int MAP_HEIGHT = 24;
const int TILE_SIZE = 32;

const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 768;

const int DEF_WHEN_CRIT = -10;
const int BASH_RENDER_TIME = 10;

using namespace std;

Map::Map()
{
	GeneratorManager::getInstance()->addGenerator("BarrerKnight", new BarrerKnightGenerator());
	mPosition = new GameVector(0, 0);
	BarrerKnight* obj1 = dynamic_cast<BarrerKnight*>( GeneratorManager::getInstance()->generatorObject("BarrerKnight"));
	obj1->setPosition({ 1400, 100 });
	mEnemy.push_back(obj1);

	//BarrerKnight* obj3 = new BarrerKnight();
	//obj3->setPosition({ 300, 100 });
	//mEnemy.push_back(obj3);

	//BarrerKnight* obj4 = new BarrerKnight();
	//obj4->setPosition({ 700, 100 });
	//mEnemy.push_back(obj4);

	//BarrerKnight* obj5 = new BarrerKnight();
	//obj5->setPosition({ 1500, 100 });
	//mEnemy.push_back(obj5);

	DroidZapper* obj2 = new DroidZapper();
	mEnemy.push_back(obj2);
	obj2->setPosition({ 1000, 100 });

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
	if (mPosition->getX() <= mPlayer->getCharWidth())
	{
		mPosition->setX(mPlayer->getCharWidth());
		if (mPlayer->getPosition()->getX() > WIN_WIDTH / 2 - 100 && mPlayer->getVelocity()->getX() > 0)
		{
			mPlayer->getPosition()->setX(mPlayer->getPosition()->getX() - mPlayer->getVelocity()->getX());
			*mPosition += *mPlayer->getVelocity();
		}
		else if (mPlayer->getPosition()->getX() < 0)
		{
			mPlayer->getPosition()->setX(0);
		}
	}
	else if (mPosition->getX() > 0 && mPosition->getX() < MAP_WIDTH * TILE_SIZE - WIN_WIDTH - 32)
	{
		mPlayer->getPosition()->setX(mPlayer->getPosition()->getX() - mPlayer->getVelocity()->getX());
		*mPosition += *mPlayer->getVelocity();
	}
	else
	{
		mPosition->setX(MAP_WIDTH * TILE_SIZE - WIN_WIDTH - 32);
		if (mPlayer->getPosition()->getX() < WIN_WIDTH / 2 && mPlayer->getVelocity()->getX() < 0)
		{
			mPlayer->getPosition()->setX(mPlayer->getPosition()->getX() - mPlayer->getVelocity()->getX());
			*mPosition += *mPlayer->getVelocity();
		}
		else if (mPlayer->getPosition()->getX() + 100 > WIN_WIDTH)
		{
			mPlayer->getPosition()->setX(WIN_WIDTH - 100);
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
		m_bFight = false;
		vector<EnemyObject*>::iterator ite = mEnemy.begin();
		while (ite != mEnemy.end())
		{
			(*ite)->processData();
			bool increase_ite = false;
			if (CollisionManager::getInstance()->checkEnemyNearPlayer(*ite) <= 400)
			{
				m_bFight = true;
			}
			if (CollisionManager::getInstance()->checkEnemyAttackPlayer(*ite) == true)
			{
				if (mPlayer->isBash() == true)
				{
					(*ite)->setStun();
					mPlayer->setAbleToCrit();
					mCountTimeRenderBash = BASH_RENDER_TIME;
				}
				else if (StatusManager::getInstance()->whenEnemyAttackPlayer(*ite) == true)
				{
					mPlayer->getHurt();
				}
			}
			if (CollisionManager::getInstance()->checkPlayerAttackEnemy(*ite) == true)
			{
				int origin = (*ite)->getStatus()->DEF;
				int luck = (*ite)->getStatus()->LUCK;
				if (mPlayer->isCrit() == true)
				{
					(*ite)->getStatus()->DEF = DEF_WHEN_CRIT;
					(*ite)->getStatus()->LUCK = 0;
				}
				if (StatusManager::getInstance()->whenPlayerAttackEnemy(*ite) == true)
				{
					std::cout << "Player is attack\n";
					(*ite)->getHurt();
					std::cout << (*ite)->getStatus()->HP << '\n';
				}
				(*ite)->getStatus()->DEF = origin;
				(*ite)->getStatus()->LUCK = luck;
			}
			else
			{
				increase_ite = true;
			}
			if ((*ite)->isAlive() == false && (*ite)->isDying() == false)
			{
				delete* ite;
				ite = mEnemy.erase(ite);
			}
			else
			{
				increase_ite = true;
			}

			if (increase_ite == true && ite != mEnemy.end())
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
		if (mEnemy[i]->getPosition()->getX() >= mPosition->getX() && mEnemy[i]->getPosition()->getX() < mPosition->getX() + WIN_WIDTH)
		{
			mEnemy[i]->setMapPosition(*mPosition);
			mEnemy[i]->renderObject();
			StatusManager::getInstance()->renderEnemyStatus(mEnemy[i]);
		}
	}
	mPlayer->renderObject();
	if (mCountTimeRenderBash > 0)
	{
		FontManager::getInstance()->drawText("Bash successfully", (int)mPlayer->getPosition()->getX(), (int)mPlayer->getPosition()->getY());
		--mCountTimeRenderBash;
	}
}