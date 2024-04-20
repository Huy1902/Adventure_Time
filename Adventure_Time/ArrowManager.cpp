#include "ArrowManager.h"

#include "CollisionManager.h"
#include "StatusManager.h"
ArrowManager* ArrowManager::s_pInstance = nullptr;

using namespace std;
void ArrowManager::addEnemyArrow(const GameVector& pos, const GameVector& mapPos, bool isRight)
{
	Arrow* newArrow = new Arrow();
	newArrow->setDirection(isRight);
	newArrow->setMapPosition(mapPos);
	newArrow->setPosition(pos);
	mEnemyArrows.push_back(newArrow);
}

bool ArrowManager::checkCollision(PlayerObject* player)
{
	for (Arrow* ite : mEnemyArrows)
	{
		SDL_Rect arrowRect{ ite->getPosition()->getX() - ite->getMapPosition()->getX(), ite->getPosition()->getY() - ite->getMapPosition()->getY(),
					ite->getAnimation()->getWidth(), ite->getAnimation()->getHeight() };
		SDL_Rect playerRect{ player->getPosition()->getX(), player->getPosition()->getY(), player->getAnimation()->getWidth(), player->getAnimation()->getHeight() };
		if (SDL_HasIntersection(&arrowRect, &playerRect))
		{
			ite->setDying();
				if (player->isBash() == false && StatusManager::getInstance()->whenEnemyAttackPlayer(ite) == true)
				{
					player->getHurt();
				}
		}
	}

	return false;
}


void ArrowManager::updateArrow()
{
	vector<Arrow*>::iterator ite = mEnemyArrows.begin();
	while (ite != mEnemyArrows.end())
	{
		if ((*ite)->isAlive() == false)
		{
			ite = mEnemyArrows.erase(ite);
		}
		else
		{
			(*ite)->setMapPosition(mMapPosition);
			(*ite)->processData();
			++ite;
		}
	}
}

void ArrowManager::renderArrow()
{
	for (Arrow* ite : mEnemyArrows)
	{
		ite->renderObject();
	}
}

ArrowManager::ArrowManager()
{
}
