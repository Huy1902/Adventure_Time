#include "JumpAction.h"
#include "GameManager.h"
#include "TextureManager.h"

JumpAction::JumpAction() :
	ActionModel(),
	m_bMiddle(false),
	mCount(-3)
{
}

JumpAction::~JumpAction()
{

}

void JumpAction::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	ActionModel::loadTexture(std::move(Info));
}

void JumpAction::processData()
{
	if (m_bOnAir == false)
	{
		m_bOnAir = true;
		m_bMiddle = false;
		mBasePosition = mPosition;
		std::cout << mPosition->getY() << '\n';
		mCount = -3;
		mIndexFrames = 0;
	}
	else
	{
		std::cout << mPosition->getY() << '\n';
		mCount += 3;
		mIndexFrames = mCount / 4;
		if (mIndexFrames == mNumFrames)
		{
			mIndexFrames = mNumFrames - 1;
			m_bOnAir = false;
		}
		//if(mIndexFrames >= )
		//if (m_bMiddle == true)
		//{
		//	if (mPosition->getY() >= mBasePosition.getY() - 40)
		//	{
		//		mIndexFrames = 2;
		//		if (mPosition->getY() >= mBasePosition.getY())
		//		{
		//			m_bOnAir = false;
		//		}

		//	}
		//}
		//else 
		//{
		//	if (mPosition->getY() <= mBasePosition.getY() - 75)
		//	{
		//		m_bMiddle = true;
		//		mIndexFrames = 1;
		//	}
		//}
	}
}

void JumpAction::renderObject() const
{
	int x = static_cast<int>(mPosition->getX());
	int y = static_cast<int>(mPosition->getY());

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
		mWidth, mHeight, GameManager::getInstance()->getRenderer(), mIndexFrames, mScope, flip);
}

void JumpAction::clearObject()
{

}
