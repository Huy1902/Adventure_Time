#include "CollisionManager.h"

CollisionManager* CollisionManager::s_pInstance = nullptr;

bool CollisionManager::checkPlayerOnGround()
{
	double x = mPlayer->getPosition()->getX();
	double y = mPlayer->getPosition()->getY();
	if (mGround->getID(x, y + 32) != -1)
	{
		mGround->optimizePositionY(y);
		mPlayer->setPositionY(y - 32);
		return true;
	}
	y += mPlayer->getHeight();
	if (mGround->getID(x, y) != -1)
	{
		mGround->optimizePositionY(y);
		mPlayer->setPositionY(y - mPlayer->getHeight());
		return true;
	}

	return false;
}

bool CollisionManager::checkPlayerHeadStuck(bool Right)
{
	double x = mPlayer->getPosition()->getX();
	double y = mPlayer->getPosition()->getY() - 10;
	if (Right == false)
	{
		x = mPlayer->getPosition()->getX() - 5;
	}
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

bool CollisionManager::checkEnemyOnGround(EnemyObject* enemy)
{
	double x = enemy->getPosition()->getX() - enemy->getMapPosition()->getX();
	double y = enemy->getPosition()->getY() - enemy->getMapPosition()->getY();
	std::cout << x << ' ' << y << '\n';
	if (mGround->getID(x, y + 32) != -1)
	{
		mGround->optimizePositionY(y);
		enemy->setPositionY(y - 32);
		return true;
	}
	y += enemy->getHeight();
	if (mGround->getID(x, y) != -1)
	{
		mGround->optimizePositionY(y);
		enemy->setPositionY(y - enemy->getHeight());
		return true;
	}

	return false;
}

bool CollisionManager::checkPlayerAttackEnemy(EnemyObject* enemy)
{
	if (mPlayer->isAttack() == true)
	{
		double e_x = enemy->getPosition()->getX() - enemy->getMapPosition()->getX();
		double e_y = enemy->getPosition()->getY() - enemy->getMapPosition()->getY();
		double p_x = mPlayer->getPosition()->getX();
		double p_y = mPlayer->getPosition()->getY();

		if (mPlayer->isRight() == true)
		{
			if (enemy->isRight() == true)
			{
				if (p_x + mPlayer->getCharWidth() > e_x)
				{
					std::cout << 1;
					return true;
				}
			}
			else
			{
				if (p_x + mPlayer->getCharWidth() > e_x - enemy->getCharWidth())
				{
					std::cout << 2;
					return true;
				}
			}
		}
		else
		{
			if (enemy->isRight() == true)
			{
				if (p_x - mPlayer->getCharWidth() < e_x + enemy->getCharWidth())
				{
					std::cout << 3;
					return true;
				}
			}
			else
			{
				if (p_x - mPlayer->getCharWidth() < e_x)
				{
					std::cout << 4;
					return true;
				}
			}
		}

	}
	return false;
}

