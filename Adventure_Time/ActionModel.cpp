#include "ActionModel.h"

#include "GameObject.h"

#include "TextureManager.h"
#include "GameManager.h"

ActionModel::ActionModel() :
	GameObject(),
	mTextureID(""),
	mIndexFrames(0),
	mPosition({0, 0}),
	mSize({ 0, 0 }),
	mNumFrames(0),
	mScope(0.0),
	m_bRight(false)
{

}

ActionModel::~ActionModel()
{

}

void ActionModel::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	mTextureID = Info->getTextureID();
	mPosition = std::make_pair(Info->getX(), Info->getY());
	mSize.setH(Info->getHeight());
	mSize.setW(Info->getWidth());
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
	int x = static_cast<int>(mPosition.getX());
	int y = static_cast<int>(mPosition.getY());

	TextureManager::getInstance()->drawSpritePic(mTextureID, x, y,
		mSize.getW(), mSize.getH(), GameManager::getInstance()->getRenderer(), mIndexFrames, mScope);
}

void ActionModel::clearObject()
{

}