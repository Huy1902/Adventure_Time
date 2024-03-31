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
#include "InputManager.h"
#include "InteractManager.h"

#include "BarrerKnight.h"
#include "DroidZapper.h"


const int mMapWidth = 120;
const int mMapHeight = 24;
const int mTileSize = 32;

const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 768;

const int DEF_WHEN_CRIT = -10;
const int BASH_RENDER_TIME = 10;

using namespace std;

Map::Map(int width, int height, int tileSize) :
	mTileSize(tileSize),
	mMapWidth(width),
	mMapHeight(height)
{
	mBackGround = new Background();
	mPosition = new GameVector(0, 0);
}

void Map::setPlayer(PlayerObject* obj)
{
	CollisionManager::getInstance()->setPlayer(obj);
	mPlayer = obj;
}

void Map::initGround()
{
	CollisionManager::getInstance()->setGround(mLayer.back());
}

//void Map::reviveCharAtBonFire()
//{
//	mPlayer->setPosition(mSavedPlayerPosition);
//	*mPosition = mSavedMapPosition;
//}

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
	else if (mPosition->getX() > 0 && mPosition->getX() < mMapWidth * mTileSize - WIN_WIDTH - 32)
	{
		mPlayer->getPosition()->setX(mPlayer->getPosition()->getX() - mPlayer->getVelocity()->getX());
		*mPosition += *mPlayer->getVelocity();
	}
	else
	{
		mPosition->setX(mMapWidth * mTileSize - WIN_WIDTH - 32);
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
					(*ite)->getHurt();
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

void Map::processEnemyAndMap()
{
	if (mEnemy.empty() == true)
	{
		m_bFight = false;
	}
	else
	{
		vector<EnemyObject*>::iterator ite = mEnemy.begin();
		while (ite != mEnemy.end())
		{
			if ((*ite)->getPosition()->getX() <= 0)
			{
				(*ite)->getPosition()->setX(0);
			}
			else if ((*ite)->getPosition()->getX() + (*ite)->getAnimation()->getWidth() > mMapWidth * mTileSize)
			{
				(*ite)->getPosition()->setX(mMapWidth * mTileSize - (*ite)->getAnimation()->getWidth() * 2);
			}
			++ite;
		}
	}
}

void Map::processInteractObjectAndPlayer()
{
	for (InteractObject* ite : mSavePoint)
	{
		ite->processData();
		ite->setMapPosition(*mPosition);
		double obj_x = ite->getPosition()->getX() - mPosition->getX();
		double obj_y = ite->getPosition()->getY() - mPosition->getY();
		if (obj_x < mPlayer->getPosition()->getX() + mPlayer->getAnimation()->getWidth()
			&& obj_x + ite->getWidth() > mPlayer->getPosition()->getX() && abs(mPlayer->getPosition()->getY() - obj_y) < 30)
		{
			InteractManager::getInstance()->takeInteract(ite, mPlayer);
		}

	}
}
void Map::updateMap()
{
	processEnemyAndPlayer();
	processMapAndPlayer();
	processEnemyAndMap();
	processInteractObjectAndPlayer();

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
		mEnemy[i]->setMapPosition(*mPosition);
		if (mEnemy[i]->getPosition()->getX() >= mPosition->getX() && mEnemy[i]->getPosition()->getX() < mPosition->getX() + WIN_WIDTH)
		{
			mEnemy[i]->renderObject();
			StatusManager::getInstance()->renderEnemyStatus(mEnemy[i]);
		}
	}
	for (InteractObject* ite : mSavePoint)
	{
		ite->renderObject();
	}
	mPlayer->renderObject();
	if (mCountTimeRenderBash > 0)
	{
		FontManager::getInstance()->drawText("Bash successfully", (int)mPlayer->getPosition()->getX(), (int)mPlayer->getPosition()->getY());
		--mCountTimeRenderBash;
	}
}