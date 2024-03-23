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

bool CollisionManager::checkEnemyNearPlayer(EnemyObject* enemy)
{
	double len = ( (*enemy->getPosition() - *enemy->getMapPosition()) - *mPlayer->getPosition()).getLength();
	if (len <= 300.0)
	{
		return true;
	}
	return false;
}

bool CollisionManager::checkEnemyAttackPlayer(EnemyObject* enemy)
{
	if (enemy->isAttack() == true)
	{
		double e_x = enemy->getPosition()->getX() - enemy->getMapPosition()->getX();
		double e_y = enemy->getPosition()->getY() - enemy->getMapPosition()->getY();
		double p_x = mPlayer->getPosition()->getX();
		double p_y = mPlayer->getPosition()->getY();
		//right
		if (p_y != e_y)
		{
			return false;
		}
		if (e_x < p_x)
		{
			if (mPlayer->isRight())
			{
				if (e_x + enemy->getAnimation()->getWidth() > p_x)
				{
					return true;
				}
			}
			else
			{
				if (e_x + enemy->getAnimation()->getWidth() > p_x)
				{
					return true;
				}
			}
		}
		else
		{
			if (mPlayer->isRight())
			{
				if (e_x + 10 < p_x + mPlayer->getCharWidth())
				{
					return true;
				}
			}
			else
			{
				if (e_x + 10< p_x + mPlayer->getCharWidth())
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool CollisionManager::checkPlayerIsRightSideWithEnemy(EnemyObject* enemy)
{
	double e_x = enemy->getPosition()->getX() - enemy->getMapPosition()->getX();
	double p_x = mPlayer->getPosition()->getX();
	if (e_x < p_x)
	{
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

		if (e_y != p_y)
		{
			return false;
		}

		if (mPlayer->isRight() == true)
		{
			if (enemy->isRight() == true)
			{
				if (p_x + mPlayer->getCharWidth() > e_x)
				{
					return true;
				}
			}
			else
			{
				if (p_x + mPlayer->getCharWidth() > e_x - enemy->getAnimation()->getWidth() + 10)
				{
					return true;
				}
			}
		}
		else
		{
			if (enemy->isRight() == true)
			{
				if (p_x - mPlayer->getCharWidth() < e_x + enemy->getAnimation()->getWidth() - 10)
				{
					return true;
				}
			}
			else
			{
				if (p_x - mPlayer->getCharWidth() < e_x)
				{
					return true;
				}
			}
		}

	}
	return false;
}

