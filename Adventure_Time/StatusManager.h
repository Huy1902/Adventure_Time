#pragma once

#include "PlayerObject.h"
class StatusManager
{
public:
	void updatePlayerStatus();
	void renderPlayerStatus();
	void setPlayer(PlayerObject* obj);

	static StatusManager* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new StatusManager();
		}
		return s_pInstance;
	}
private:
	static StatusManager* s_pInstance;
	int HP;
	PlayerObject* mPlayer;

	SDL_Rect mSrcPoint;
	SDL_Rect mDestPoint;
	SDL_Rect mSrcHealth;
	SDL_Rect mDestHealth;
	Status mCurrentPlayer;
	Status mMaxPlayer;

	int mDecreasePoint;
	int mLenPoint;

	StatusManager();
	~StatusManager();
};

