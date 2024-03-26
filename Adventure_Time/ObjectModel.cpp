#include "ObjectModel.h"

#include "BaseObject.h"

#include "TextureManager.h"
#include "GameManager.h"

ObjectModel::ObjectModel() :
	BaseObject()
{

}

ObjectModel::~ObjectModel()
{
	delete mPosition;
}

void ObjectModel::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	mTextureID = Info->getTextureID();
	mPosition = new GameVector(Info->getX() , Info->getY());
	mHeight = Info->getHeight();
	mWidth = Info->getWidth();
	mNumFrames = Info->getNumFrames();
	mScope = Info->getScope();
}

void ObjectModel::processData()
{
	++mIndexFrames;
	if (mIndexFrames == mNumFrames)
	{
		mIndexFrames = 0;
	}
}

void ObjectModel::renderObject() const
{
	int x = static_cast<int>(mPosition->getX());
	int y = static_cast<int>(mPosition->getY());

	TextureManager::getInstance()->drawSpritePicByCol(mTextureID, x, y,
		mWidth, mHeight, GameManager::getInstance()->getRenderer(), mIndexFrames, mScope, SDL_FLIP_NONE);
}

void ObjectModel::clearObject()
{

}