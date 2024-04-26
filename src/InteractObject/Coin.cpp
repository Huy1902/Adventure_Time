#include "Coin.h"

#include "TextureManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "FontManager.h"

Coin::Coin()
{
	mPosition = new GameVector();
	mMapPosition = new GameVector();

	mTextureID = "MonedaD";
	mHeight = 16;
	mWidth = 16;
	mNumFrames = 5;
	mType = COIN;
}


bool Coin::interactItem()
{
	//auto to claim
	return true;
}

Coin::~Coin()
{
}

void Coin::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	mTextureID = Info->getTextureID();
	mPosition = new GameVector(Info->getX(), Info->getY());
	mHeight = Info->getHeight();
	mWidth = Info->getWidth();
	mNumFrames = Info->getNumFrames();
}

void Coin::processData()
{
	++mIndexFrames;
	if (mIndexFrames == mNumFrames)
	{
		mIndexFrames = 0;
	}
	m_bAbleToInteract = false;
}

void Coin::renderObject() const
{
	int x = static_cast<int>(mPosition->getX() - mMapPosition->getX());
	int y = static_cast<int>(mPosition->getY() - mMapPosition->getY());

	TextureManager::getInstance()->drawSpritePicByCol(mTextureID, x, y,
		mWidth, mHeight, GameManager::getInstance()->getRenderer(), mIndexFrames, SDL_FLIP_NONE);
}

void Coin::clearObject()
{

}
