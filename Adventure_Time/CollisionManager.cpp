#include "CollisionManager.h"

CollisionManager* CollisionManager::s_pInstance = nullptr;

bool CollisionManager::checkPlayerOnGround()
{
	double x = mPlayer->getPosition()->getX();
	if (mPlayer->isRight() == true)
	{
		x += mPlayer->getAnimation()->getWidth() / 2;
	}
	else
	{
		x += mPlayer->getAnimation()->getWidth() / 2;
	}
	double y = mPlayer->getPosition()->getY();
	if (mGround->getID(x + 10, y + 32) != -1)
	{
		mGround->optimizePositionY(y);
		mPlayer->setPositionY(y - 32);
		return true;
	}
	if (mGround->getID(x - 10, y + 32) != -1)
	{
		mGround->optimizePositionY(y);
		mPlayer->setPositionY(y - 32);
		return true;
	}
	y += mPlayer->getHeight();
	if (mGround->getID(x + 10, y) != -1)
	{
		mGround->optimizePositionY(y);
		mPlayer->setPositionY(y - mPlayer->getHeight());
		return true;
	}
	if (mGround->getID(x - 10, y) != -1)
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
	double y = mPlayer->getPosition()->getY() - 2;
	//if (mPlayer->isRight() == true)
	//{
	if (mGround->getID(x + mPlayer->getAnimation()->getWidth() / 2 - 10, y) != -1)
	{
		return true;
	}
	if (mGround->getID(x + mPlayer->getAnimation()->getWidth() / 2 + 10, y) != -1)
	{
		return true;
	}
	//}
	//else
	//{
	//	x += mPlayer->getCharWidth() / 2;
	//}
	///*if (Right == false)
	//{
	//	x = mPlayer->getPosition()->getX() - 5;
	//}*/
	//if (mGround->getID(x, y) != -1)
	//{
	//	return true;
	//}
	return false;
}

bool CollisionManager::checkPlayerSideLeft()
{
	double x = mPlayer->getPosition()->getX() ;
	for (double y = mPlayer->getPosition()->getY(), range = y + mPlayer->getHeight(); y < range; y += 32)
	{
		if (mGround->getID(x, y) != -1)
		{
			return true;
		}
	}
	for (double y = mPlayer->getPosition()->getY(), range = y + mPlayer->getHeight(); y < range; y += 32)
	{
		if (mGround->getID(x + 16, y) != -1)
		{
			return true;
		}
	}
	return false;
}

bool CollisionManager::checkPlayerSideRight()
{
	double x = mPlayer->getPosition()->getX() + 76;
	for (double y = mPlayer->getPosition()->getY(), range = y + mPlayer->getHeight(); y < range; y += 32)
	{
		if (mGround->getID(x, y) != -1)
		{
			return true;
		}
	}
	for (double y = mPlayer->getPosition()->getY(), range = y + mPlayer->getHeight(); y < range; y += 32)
	{
		if (mGround->getID(x - 16, y) != -1)
		{
			return true;
		}
	}
	return false;
}

bool CollisionManager::checkEnemyOnGround(EnemyObject* enemy)
{
	double x = enemy->getPosition()->getX() - enemy->getMapPosition()->getX() + enemy->getAnimation()->getWidth() / 2;
	double y = enemy->getPosition()->getY() - enemy->getMapPosition()->getY();
	if (mGround->getID(x, y + 32) != -1)
	{
		mGround->optimizePositionY(y);
		enemy->setPositionY(y - 32);
		return true;
	}
	y += enemy->getAnimation()->getHeight();
	if (mGround->getID(x, y) != -1)
	{
		mGround->optimizePositionY(y);
		enemy->setPositionY(y - enemy->getAnimation()->getHeight());
		return true;
	}

	return false;
}

int CollisionManager::checkEnemyNearPlayer(EnemyObject* enemy)
{
	double len = ((*enemy->getPosition() - *enemy->getMapPosition()) - *mPlayer->getPosition()).getLength();
	return (int)len;
}

bool CollisionManager::checkEnemyAttackPlayer(EnemyObject* enemy)
{
	if (enemy->isAttack() == true)
	{
		double e_x = enemy->getPosition()->getX() - enemy->getMapPosition()->getX() + enemy->getAnimation()->getWidth() / 2;
		double e_y = enemy->getPosition()->getY() - enemy->getMapPosition()->getY();
		double p_x = mPlayer->getPosition()->getX() + mPlayer->getAnimation()->getWidth() / 2;
		double p_y = mPlayer->getPosition()->getY();
		//right
		if (abs(p_y - e_y) > 0)
		{
			return false;
		}
		if (e_x < p_x)
		{
			/*if (mPlayer->isRight())
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
			}*/
			if (e_x + enemy->getAnimation()->getWidth() / 2 > p_x - mPlayer->getAnimation()->getWidth() / 2)
			{
				return true;
			}
		}
		else
		{
			/*if (mPlayer->isRight())
			{
				if (e_x < p_x + mPlayer->getCharWidth())
				{
					return true;
				}
			}
			else
			{
				if (e_x < p_x + mPlayer->getCharWidth())
				{
					return true;
				}
			}*/
			if (e_x - enemy->getAnimation()->getWidth() / 2 < p_x + mPlayer->getAnimation()->getWidth() / 2)
			{
				return true;
			}
		}
	}
	return false;
}

bool CollisionManager::checkPlayerIsRightSideWithEnemy(EnemyObject* enemy)
{
	double e_x = enemy->getPosition()->getX() - enemy->getMapPosition()->getX() + enemy->getAnimation()->getWidth() / 2;
	double p_x = mPlayer->getPosition()->getX() + mPlayer->getAnimation()->getWidth() / 2;
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
		double e_x = enemy->getPosition()->getX() - enemy->getMapPosition()->getX() + enemy->getAnimation()->getWidth() / 2;
		double e_y = enemy->getPosition()->getY() - enemy->getMapPosition()->getY();
		double p_x = mPlayer->getPosition()->getX() + mPlayer->getAnimation()->getWidth() / 2;
		double p_y = mPlayer->getPosition()->getY();
		//right
		if (abs(p_y - e_y) > 0)
		{
			return false;
		}
		if (e_x < p_x)
		{
			/*if (mPlayer->isRight())
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
			}*/
			if (e_x + enemy->getCharWidth() / 2 > p_x - mPlayer->getAnimation()->getWidth() / 2)
			{
				return true;
			}
		}
		else
		{
			/*if (mPlayer->isRight())
			{
				if (e_x < p_x + mPlayer->getCharWidth())
				{
					return true;
				}
			}
			else
			{
				if (e_x < p_x + mPlayer->getCharWidth())
				{
					return true;
				}
			}*/
			if (e_x - enemy->getCharWidth() / 2 < p_x + mPlayer->getAnimation()->getWidth() / 2)
			{
				return true;
			}
		}
	}
	return false;
	return false;
}

