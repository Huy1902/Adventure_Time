#include "CollisionManager.h"

CollisionManager* CollisionManager::s_pInstance = nullptr;

bool CollisionManager::checkPlayerOnGround()
{
	double x = mPlayer->getPosition()->getX();
	double y = mPlayer->getPosition()->getY();
	y += mPlayer->getHeight();
	if (mGround->getID(x, y) != -1)
	{
		mGround->optimizePositionY(y);
		mPlayer->setPositionY(y - mPlayer->getHeight());
		return true;
	}

	return false;
}

bool CollisionManager::checkPlayerHeadStuck()
{
	double x = mPlayer->getPosition()->getX();
	double y = mPlayer->getPosition()->getY() - 10;
	if (mGround->getID(x, y) != -1)
	{
		return true;
	}
	return false;
}

bool CollisionManager::checkPlayerSideLeft()
{
	double x = mPlayer->getPosition()->getX() - 32;
	for (double y = mPlayer->getPosition()->getY(), range = y + mPlayer->getHeight(); y < range; y += 20)
	{
		if (mGround->getID(x, y) != -1)
		{
			return true;
		}
	}
	return false;
}

bool CollisionManager::checkPlayerSideRight()
{
	double x = mPlayer->getPosition()->getX() + 32;
	for (double y = mPlayer->getPosition()->getY(), range = y + mPlayer->getHeight(); y < range; y += 20)
	{
		if (mGround->getID(x, y) != -1)
		{
			return true;
		}
	}
	return false;
}