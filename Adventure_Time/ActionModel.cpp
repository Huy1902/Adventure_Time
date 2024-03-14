#include "ActionModel.h"

#include "BaseObject.h"

#include "TextureManager.h"
#include "GameManager.h"

ActionModel::ActionModel() :
	BaseObject(),
	m_bRight(false),
	m_bOnAir(false)
{

}

ActionModel::~ActionModel()
{

}

void ActionModel::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	mTextureID = Info->getTextureID();
	mPosition = new GameVector(Info->getX(), Info->getY());
	mHeight = Info->getHeight();
	mWidth = Info->getWidth();
	mNumFrames = Info->getNumFrames();
	mScope = Info->getScope();
}

void ActionModel::processData()
{
	++mIndexFrames;
	if (mIndexFrames == mNumFrames)
	{
		mIndexFrames = 0;
	}
}

void ActionModel::renderObject() const
{
	int x = static_cast<int>(mPosition->getX());
	int y = static_cast<int>(mPosition->getY());

	TextureManager::getInstance()->drawSpritePic(mTextureID, x, y,
		mWidth, mHeight, GameManager::getInstance()->getRenderer(), mIndexFrames, mScope);
}

void ActionModel::clearObject()
{

}