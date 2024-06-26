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
		mPlayer->getPosition()->setY(y - 32);
		return true;
	}
	if (mGround->getID(x - 10, y + 32) != -1)
	{
		mGround->optimizePositionY(y);
		mPlayer->getPosition()->setY(y - 32);
		return true;
	}
	y += mPlayer->getHeight();
	if (mGround->getID(x + 10, y) != -1)
	{
		mGround->optimizePositionY(y);
		mPlayer->getPosition()->setY(y - mPlayer->getHeight());
		return true;
	}
	if (mGround->getID(x - 10, y) != -1)
	{
		mGround->optimizePositionY(y);
		mPlayer->getPosition()->setY(y - mPlayer->getHeight());
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
	double x = mPlayer->getPosition()->getX() + 100;
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

bool CollisionManager::checkEnemySideLeft(EnemyObject* enemy)
{
	double e_x = enemy->getPosition()->getX() - 10;
	double e_y = enemy->getPosition()->getY();
	if (mGround->getIDNoBaseOnMap(e_x, e_y) != -1)
	{
		return true;
	}
	return false;
}

bool CollisionManager::checkEnemySideRight(EnemyObject* enemy)
{
	double e_x = enemy->getPosition()->getX() + enemy->getAnimation()->getWidth() + 10; 
	double e_y = enemy->getPosition()->getY();
	//system("pause");
	if (mGround->getIDNoBaseOnMap(e_x, e_y) != -1)
	{
		return true;
	}
	return false;
}

bool CollisionManager::checkEnemyOnGround(EnemyObject* enemy)
{
	double x = enemy->getPosition()->getX() + enemy->getAnimation()->getWidth() / 2;
	//std::cout << enemy->getPosition()->getX() << ' ' << enemy->getMapPosition()->getX() << '\n';
	double y = enemy->getPosition()->getY() ;
	if (mGround->getIDNoBaseOnMap(x, y + 32) != -1)
	{
		mGround->optimizePositionY(y);
		enemy->getPosition()->setY(y - 32);
		return true;
	}
	y += enemy->getAnimation()->getHeight();
	if (mGround->getIDNoBaseOnMap(x, y) != -1)
	{
		mGround->optimizePositionY(y);
		enemy->getPosition()->setY(y - enemy->getAnimation()->getHeight());
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
		double e_y = enemy->getPosition()->getY() - enemy->getMapPosition()->getY() + enemy->getHeight();
		double p_x = mPlayer->getPosition()->getX() + mPlayer->getAnimation()->getWidth() / 2;
		double p_y = mPlayer->getPosition()->getY();
		//right
		if (abs(p_y - e_y ) > 0)
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
			if (e_x + enemy->getAnimation()->getWidth() / 2 - enemy->getAttackRange() > p_x - mPlayer->getAnimation()->getWidth() / 2)
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
			if (e_x - enemy->getAnimation()->getWidth() / 2 + enemy->getAttackRange() < p_x + mPlayer->getAnimation()->getWidth() / 2)
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
		double e_y = enemy->getPosition()->getY() - enemy->getMapPosition()->getY() + enemy->getHeight();
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
}

