#pragma once
#include "GameVector.h"
class InteractManager
{
public:
	static InteractManager* getInstance()
	{
		if (s_pIntance == nullptr)
		{
			s_pIntance = new InteractManager();
		}
		return s_pIntance;
	}
	void setSavedPos(const GameVector& map_pos, const GameVector& player_pos)
	{
		*mSavedMapPos = map_pos;
		*mSavedPlayerPos = player_pos;
	}
	GameVector* getSavedPlayerPos()
	{
		return mSavedPlayerPos;
	}
	GameVector* getSavedMapPos()
	{
		return mSavedMapPos;
	}
private:
	static InteractManager* s_pIntance;

	InteractManager();
	~InteractManager();
	GameVector* mSavedPlayerPos;
	GameVector* mSavedMapPos;
};

