#include "RunAction.h"

#include "GameManager.h"
#include "TextureManager.h"
RunAction::RunAction() :
	ActionModel()
{

}

RunAction::~RunAction()
{

}

void RunAction::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	ActionModel::loadTexture(std::move(Info));
}

void RunAction::processData()
{
	++mIndexFrames;
	if (mIndexFrames == mNumFrames)
	{
		mIndexFrames = 0;
	}
}

void RunAction::renderObject() const
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

void RunAction::clearObject()
{

}
