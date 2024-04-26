#include "EnemyObject.h"
#include "GameManager.h"
#include "InputManager.h"

#include "CollisionManager.h"

#include "StatusManager.h"

EnemyObject::EnemyObject()
{
	mCharHeight = 0;
	mAttackRange = 0;
	mMapPosition = new GameVector();
}

EnemyObject::~EnemyObject()
{
	StatusManager::getInstance()->setScore(StatusManager::getInstance()->getScore() + 10);
	delete mMapPosition;
}


void EnemyObject::processData()
{
}

void EnemyObject::renderObject() const
{
	AnimModel::renderObject();
}

void EnemyObject::clearObject()
{

}

bool EnemyObject::sideStuck(EnemyObject* obj)
{
	if ( (CollisionManager::getInstance()->checkEnemySideLeft(obj) && obj->isRight() == false) || 
		(CollisionManager::getInstance()->checkEnemySideRight(obj) && obj->isRight() == true) )
	{
		return true;
	}
	return false;
}
