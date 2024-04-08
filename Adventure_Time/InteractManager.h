#ifndef INTERACTMANAGER_H_
#define INTERACTMANAGER_H_
#include "GameVector.h"
#include "PlayerObject.h"
#include "InteractObject.h"

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
	bool takeInteract(InteractObject* obj, PlayerObject* player);
private:
	static InteractManager* s_pIntance;
	void savePoint(InteractObject* obj, PlayerObject* player);
	void takeCoin(InteractObject* obj);
	void portal(InteractObject* obj);
	InteractManager();
	~InteractManager();
	GameVector* mSavedPlayerPos;
	GameVector* mSavedMapPos;
};

#endif

