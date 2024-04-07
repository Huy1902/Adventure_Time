#include "Portal.h"

#include "TextureManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "FontManager.h"

#include "MapManager.h"

Portal::Portal()
{
	mPosition = new GameVector();
	mMapPosition = new GameVector();

	mTextureID = "Portal";
	mHeight = 60;
	mWidth = 40;
	mNumFrames = 9;
	mType = SAVE_POINT;
}


bool Portal::interactItem()
{
	m_bAbleToInteract = true;
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_F))
	{
		
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
}

void Portal::processData()
{
	++mIndexFrames;
	if (mIndexFrames == mNumFrames)
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
		mWidth, mHeight, GameManager::getInstance()->getRenderer(), mIndexFrames, SDL_FLIP_NONE);

	if (m_bAbleToInteract == true)
	{
		FontManager::getInstance()->drawText("Press F to Interact", x, y);
	}
}

void Portal::clearObject()
{

}