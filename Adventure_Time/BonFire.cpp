#include "BonFire.h"

#include "TextureManager.h"
#include "GameManager.h"

BonFire::BonFire()
{
	mPosition = new GameVector();
	mMapPosition = new GameVector();

	mTextureID = "bonfire";
	mHeight = 60;
	mWidth = 40;
	mNumFrames = 9;
}


BonFire::~BonFire()
{
	delete mPosition;
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
}

void BonFire::renderObject() const
{
	int x = static_cast<int>(mPosition->getX() - mMapPosition->getX());
	int y = static_cast<int>(mPosition->getY() - mMapPosition->getY());

	TextureManager::getInstance()->drawSpritePicByCol(mTextureID, x, y,
		mWidth, mHeight, GameManager::getInstance()->getRenderer(), mIndexFrames, SDL_FLIP_NONE);
}

void BonFire::clearObject()
{

}