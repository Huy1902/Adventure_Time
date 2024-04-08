#include "Portal.h"

#include "TextureManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "FontManager.h"
#include "MapManager.h"
#include "GameManager.h"

#include "LoadingState.h"

Portal::Portal()
{
	mPosition = new GameVector();
	mMapPosition = new GameVector();

	mTextureID = "Portal";
	mHeight = 80;
	mWidth = 80;
	mNumFrames = 6;
	mType = PORTAL;
}


bool Portal::interactItem()
{
	m_bAbleToInteract = true;
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_F))
	{
		MapManager::getInstance()->changeMapFromTo(mFrom, mTo);
		GameManager::getInstance()->getFSM()->changeState(new LoadingState());
		return true;
	}
	return false;
}

Portal::~Portal()
{
	delete mPosition;
	delete mMapPosition;
}

void Portal::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	mTextureID = Info->getTextureID();
	mPosition = new GameVector(Info->getX(), Info->getY());
	mHeight = Info->getHeight();
	mWidth = Info->getWidth();
	mNumFrames = Info->getNumFrames();
	mFrom = Info->getFrom();
	mTo = Info->getTo();
}

void Portal::processData()
{
	++mIndexFrames;
	if (mIndexFrames == mNumFrames * 5)
	{
		mIndexFrames = 0;
	}
	m_bAbleToInteract = false;
}

void Portal::renderObject() const
{
	int x = static_cast<int>(mPosition->getX() - mMapPosition->getX());
	int y = static_cast<int>(mPosition->getY() - mMapPosition->getY());

	TextureManager::getInstance()->drawSpritePicByCol(mTextureID, x, y,
		mWidth, mHeight, GameManager::getInstance()->getRenderer(), mIndexFrames / 5, SDL_FLIP_NONE);

	if (m_bAbleToInteract == true)
	{
		FontManager::getInstance()->drawText("Press F to Interact", x, y);
	}
}

void Portal::clearObject()
{

}