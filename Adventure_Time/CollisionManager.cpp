#include "CollisionManager.h"

CollisionManager* CollisionManager::s_pInstance = nullptr;

bool CollisionManager::checkPlayerOnGround()
{
	int x = mPlayer->getPosition()->getX();
	int y = mPlayer->getPosition()->getY();
	y += mPlayer->getHeight();
	if (mGround->getID(x, y) != -1)
	{
		mPlayer->setPositionY(y - mPlayer->getHeight());
		return true;
	}

	return false;
}

bool CollisionManager::checkPlayerHeadStuck()
{
	int x = mPlayer->getPosition()->getX();
	int y = mPlayer->getPosition()->getY() - 30;
	if (mGround->getID(x, y) != -1)
	{
		return true;
	}
	//y = mPlayer->getPosition()->getY() - 10;
	//if (mGround->getID(x, y) != -1)
	//{
	//	return true;
	//}
	return false;
}
