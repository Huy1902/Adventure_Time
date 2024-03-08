#include "PlayerObject.h"
#include "GameManager.h"

PlayerObject::PlayerObject() :
	ObjectModel()
{

}

PlayerObject::~PlayerObject()
{

}

void PlayerObject::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	ObjectModel::loadTexture(std::move(Info));
}

void PlayerObject::processData()
{
	mPosition.setX(mPosition.getX() + 10);
	mPosition.setY(mPosition.getY() + 10);
	if (mPosition.getX() == GameManager::getInstance()->getHeightWindows())
	{
		mPosition.setX(0);
		mPosition.setY(0);
	}
	++mIndexFrames;
	if (mIndexFrames == mNumFrames)
	{
		mIndexFrames = 0;
	}
}

void PlayerObject::renderObject() const
{
	ObjectModel::renderObject();
}

void PlayerObject::cleanObject()
{

}
