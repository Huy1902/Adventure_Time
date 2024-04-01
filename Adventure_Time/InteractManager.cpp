#include "InteractManager.h"

#include "StatusManager.h"
InteractManager* InteractManager::s_pIntance = nullptr;

bool InteractManager::takeInteract(InteractObject* obj, PlayerObject* player)
{
	switch (obj->getType())
	{
	case NOTHING:
		break;
	case SAVE_POINT:
		savePoint(obj, player);
		break;
	case COIN:
		takeCoin(obj);
		return true;
		break;
	default:
		break;
	}
	return false;
}

void InteractManager::savePoint(InteractObject* obj, PlayerObject* player)
{
	if (obj->interactItem())
	{
		*mSavedMapPos = *obj->getMapPosition();
		*mSavedPlayerPos = *player->getPosition();
	}
}

void InteractManager::takeCoin(InteractObject* obj)
{
	StatusManager::getInstance()->setScore(StatusManager::getInstance()->getScore() + 1);
	delete obj;
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
