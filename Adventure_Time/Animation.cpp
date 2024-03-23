#include "Animation.h"
#include "GameManager.h"
#include "TextureManager.h"

//Animation* Animation::s_pInstance = nullptr;
int count = 0;

void Animation::update()
{
	++mIndexFrame;
	if (mIndexFrame >= mNumFrame * mSpeed)
	{
		mIndexFrame = 0;
	}
}

void Animation::draw()
{
	TextureManager::getInstance()->drawSpritePic(mTextureID, mPosition.getX(), mPosition.getY(), mW, mH, GameManager::getInstance()->getRenderer(), mIndexFrame / mSpeed, 1.0, mFlip);
}

void Animation::changeAnim(const std::string& textureID, const int& numFrame, SDL_RendererFlip flip)
{
	if (textureID != mTextureID)
	{
		mIndexFrame = 0;
		mTextureID = textureID;
		mNumFrame = numFrame;
		mSpeed = 1;
	}
	mFlip = flip;
}
void Animation::changeAnim(const std::string& textureID, const int& numFrame, SDL_RendererFlip flip, const int& w, const int& h, const int& speed)
{
	if (textureID != mTextureID)
	{
		mIndexFrame = 0;
		mTextureID = textureID;
		mNumFrame = numFrame;
		mSpeed = speed;
		mW = w;
		mH = h;
	}
	mFlip = flip;

}

Animation::Animation()
{
	mIndexFrame = 0;
	mSpeed = 1;
}
