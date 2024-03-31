#include "InteractManager.h"

InteractManager* InteractManager::s_pIntance = nullptr;

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
