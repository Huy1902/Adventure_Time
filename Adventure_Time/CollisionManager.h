#pragma once

#include "Layer.h"
#include "PlayerObject.h"

#include "EnemyObject.h"
class CollisionManager
{
public:
	bool checkPlayerOnGround();
	bool checkPlayerHeadStuck(bool Right);
	bool checkPlayerSideLeft();
	bool checkPlayerSideRight();

	bool checkEnemyOnGround(EnemyObject* enemy);

	bool checkPlayerAttackEnemy(EnemyObject* enemy);

	void setGround(Layer* obj)
	{
		mGround = obj;
	}
	void setPlayer(PlayerObject* obj)
	{
		mPlayer = obj;
	}

	static CollisionManager* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new CollisionManager();
		}
		return s_pInstance;
	}
private:
	Layer* mGround;
	PlayerObject* mPlayer;

	static CollisionManager* s_pInstance;

	CollisionManager() {};
	~CollisionManager() {};
};

