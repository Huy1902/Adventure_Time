#include "BonFire.h"

#include "TextureManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "FontManager.h"

BonFire::BonFire()
{
	mPosition = new GameVector();
	mMapPosition = new GameVector();

	mTextureID = "bonfire";
	mHeight = 60;
	mWidth = 40;
	mNumFrames = 9;
	mType = SAVE_POINT;
}


bool BonFire::interactItem()
{
	m_bAbleToInteract = true;
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_F))
	{
		return true;
	}
	return false;
}

BonFire::~BonFire()
{
	delete mPosition;
	delete mMapPosition;
}

void BonFire::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	mTextureID = Info->getTextureID();
	mPosition = new GameVector(Info->getX(), Info->getY());
	mHeight = Info->getHeight();
	mWidth = Info->getWidth();
	mNumFrames = Info->getNumFrames();
}

void BonFire::processData()
{
	++mIndexFrames;
	if (mIndexFrames == mNumFrames)
	{
		mIndexFrames = 0;
	}
	m_bAbleToInteract = false;
}

void BonFire::renderObject() const
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

void BonFire::clearObject()
{

}