#include "ObjectModel.h"

#include "GameObject.h"

#include "TextureManager.h"
#include "GameManager.h"

ObjectModel::ObjectModel() :
	GameObject(),
	mTextureID(""),
	mIndexFrames(0),
	mXPos(0),
	mYPos(0),
	mWidth(0),
	mHeight(0),
	mNumFrames(0),
	mScope(1.0)
{

}

ObjectModel::~ObjectModel()
{

}

void ObjectModel::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	mTextureID = Info->getTextureID();
	mXPos = Info->getX();
	mYPos = Info->getY();
	mWidth = Info->getWidth();
	mHeight = Info->getHeight();
	mNumFrames = Info->getNumFrames();
	mScope = Info->getScope();
}

void ObjectModel::processData()
{
	++mXPos;
	++mIndexFrames;
	if (mIndexFrames == mNumFrames)
	{
		mIndexFrames = 0;
	}
}

void ObjectModel::renderObject() const
{
	TextureManager::getInstance()->drawSpritePic(mTextureID, mXPos, mYPos, mWidth, mHeight,
		GameManager::getInstance()->getRenderer(), mIndexFrames, mScope);
}

void ObjectModel::cleanObject()
{

}