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
	mXPos += 10;
	mYPos += 10;
	if (mYPos == GameManager::getInstance()->getHeightWindows())
	{
		mXPos = 0;
		mYPos = 0;
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
