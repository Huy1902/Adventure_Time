#include "RunAction.h"

#include "GameManager.h"
#include "TextureManager.h"

#include "InputManager.h"
#include "PlayerObject.h"

std::string RunAction::mActionID = "Run";

RunAction::RunAction() :
	ActionModel(),
	mVelocity(nullptr)
{
	mNumFrames = 7;
	mIndexFrames = 0;
}

RunAction::~RunAction()
{

}

void RunAction::processData()
{
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_D) == true)
	{

	}
	else if (InputManager::getInstance()->keyDown(SDL_SCANCODE_A) == true)
	{

	}
	else if (InputManager::getInstance()->keyDown(SDL_SCANCODE_K) == true)
	{
		mFromRunToJump();
	}
	else if (InputManager::getInstance()->keyDown(SDL_SCANCODE_L) == true)
	{
		mFromRunToDash();
	}
	else
	{
		mFromRunToIdle();
	}
	++mIndexFrames;
	if (mIndexFrames == mNumFrames)
	{
		mIndexFrames = 0;
	}
}

void RunAction::renderAction()
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
		mWidth, mHeight, GameManager::getInstance()->getRenderer(), mIndexFrames, 1.0, flip);
}

bool RunAction::onEnter()
{
	mPosition = new GameVector(0, 0);
	mVelocity = new GameVector(0, 0);

	TextureManager::getInstance()->load("assets/knight_player/Walking_KG_1.png", "run",
		GameManager::getInstance()->getRenderer());


	return true;
}

bool RunAction::onExit()
{
	delete mPosition;
	delete mVelocity;
	return true;
}

void RunAction::mFromRunToDash()
{
	PlayerObject::getPlayerObject()->getActionMachine()->changeAction(new JumpAction());
}

void RunAction::mFromRunToJump()
{

}

void RunAction::mFromRunToIdle()
{
	PlayerObject::getPlayerObject()->getActionMachine()->pushAction(new IdleAction());
}