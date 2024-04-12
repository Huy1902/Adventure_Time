#include "EnemyObject.h"
#include "GameManager.h"
#include "InputManager.h"

#include "CollisionManager.h"

#include "StatusManager.h"

EnemyObject::EnemyObject()
{
	mCharHeight = 0;
	mAttackRange = 0;
}

EnemyObject::~EnemyObject()
{
	StatusManager::getInstance()->setScore(StatusManager::getInstance()->getScore() + 10);
	delete mMapPosition;
}

void EnemyObject::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	ObjectModel::loadTexture(std::move(Info));
}

void EnemyObject::processData()
{
	++mIndexFrames;
	if (mIndexFrames == mNumFrames)
	{
		mIndexFrames = 0;
	} 
}

void EnemyObject::renderObject() const
{
	ObjectModel::renderObject();
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
