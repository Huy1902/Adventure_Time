#include "InteractManager.h"


InteractManager* InteractManager::s_pIntance = nullptr;

void InteractManager::takeInteract(InteractObject* obj, PlayerObject* player)
{
	switch (obj->getType())
	{
	case NOTHING:
		break;
	case SAVE_POINT:
		savePoint(obj, player);
		break;
	case COIN:
		takeCoin();
		break;
	default:
		break;
	}
}

void InteractManager::savePoint(InteractObject* obj, PlayerObject* player)
{
	if (obj->interactItem())
	{
		*mSavedMapPos = *obj->getMapPosition();
		*mSavedPlayerPos = *player->getPosition();
	}
}

void InteractManager::takeCoin()
{
}

InteractManager::InteractManager()
{
	mSavedMapPos = new GameVector(0, 0);
	mSavedPlayerPos = new GameVector(200, 100);
}

InteractManager::~InteractManager()
{
	delete mSavedMapPos;
	delete mSavedPlayerPos;
}
