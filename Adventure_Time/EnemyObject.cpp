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
	mPosition.setX(mPosition.getX() + 10);
	if (mPosition.getX() == GameManager::getInstance()->getWidthWindows())
	{
		mPosition.setX(0);
		mPosition.setY(mPosition.getY() + 100);
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
