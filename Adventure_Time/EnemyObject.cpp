#include "EnemyObject.h"
#include "GameManager.h"

EnemyObject::EnemyObject() :
	ObjectModel()
{

}

EnemyObject::~EnemyObject()
{

}

void EnemyObject::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	ObjectModel::loadTexture(std::move(Info));
}

void EnemyObject::processData()
{
	mXPos += 10;
	if (mXPos == GameManager::getInstance()->getWidthWindows())
	{
		mXPos = 0;
		mYPos += 100;
	}
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

void EnemyObject::cleanObject()
{

}
