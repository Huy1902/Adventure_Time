#pragma once

#include "Layer.h"
#include "PlayerObject.h"
class CollisionManager
{
public:
	bool checkPlayerOnGround();
	bool checkPlayerHeadStuck();

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

