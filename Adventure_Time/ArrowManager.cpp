#include "ArrowManager.h"

ArrowManager* ArrowManager::s_pInstance = nullptr;

void ArrowManager::updateArrow()
{
	for (Arrow* ite : mEnemyArrows)
	{
		ite->processData();
	}
}

void ArrowManager::renderArrow()
{
	for (Arrow* ite : mEnemyArrows)
	{
		ite->renderObject();
	}
}

ArrowManager::ArrowManager()
{
	Arrow* newArrow = new Arrow();
	newArrow->setMapPosition(GameVector(0, 0));
	newArrow->setPosition(GameVector(100, 100));
	//newArrow->setDirection(GameVector(-20, 20));
	mEnemyArrows.push_back(newArrow);
}
