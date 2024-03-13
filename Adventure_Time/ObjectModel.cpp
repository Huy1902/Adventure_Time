#include "ObjectModel.h"

#include "BaseObject.h"

#include "TextureManager.h"
#include "GameManager.h"

ObjectModel::ObjectModel() :
	BaseObject(),
	mTextureID(""),
	mIndexFrames(0),
	mSize({0, 0}),
	mPosition({ 0, 0 }),
	mNumFrames(0),
	mScope(1.0),
	mCurrentAction(nullptr),
	m_bRight(true)
{

}

ObjectModel::~ObjectModel()
{

}

void ObjectModel::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	mTextureID = Info->getTextureID();
	mPosition = std::make_pair(Info->getX() , Info->getY());
	mSize.setH(Info->getHeight());
	mSize.setW(Info->getWidth());
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
	int x = static_cast<int>(mPosition.getX());
	int y = static_cast<int>(mPosition.getY());

	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (m_bRight == true)
	{
		flip = SDL_FLIP_NONE;
	}
	else
	{
		flip = SDL_FLIP_HORIZONTAL;
	}

	TextureManager::getInstance()->drawSpritePic(mTextureID, x, y,
		mSize.getW(), mSize.getH(), GameManager::getInstance()->getRenderer(), mIndexFrames, mScope, flip);
}

void ObjectModel::clearObject()
{

}