#include "EnemyObject.h"
#include "GameManager.h"
#include "InputManager.h"

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
