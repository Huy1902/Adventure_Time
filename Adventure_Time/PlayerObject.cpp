#include "PlayerObject.h"

#include "GameManager.h"
#include "RunAction.h"
#include "JumpAction.h"
#include "InputManager.h"

PlayerObject::PlayerObject() :
	ObjectModel()
{
	RunAction* run = new RunAction();
	run->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("run", 0, 0, 64, 64, 8, 2.5)));
	mActionMap["run"] = run;

	JumpAction* jump = new JumpAction();
	jump->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("jump", 0, 0, 64, 64, 3, 2.5)));
	mActionMap["jump"] = jump;
	mCurrentAction = mActionMap["jump"];
}

PlayerObject::~PlayerObject()
{

}

void PlayerObject::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	ObjectModel::loadTexture(std::move(Info));
}

void PlayerObject::processData()
{
	InputManager::getInstance()->takeInput();
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_SPACE))
	{
		mCurrentAction = mActionMap["jump"];
	}
	else if(InputManager::getInstance()->keyDown(SDL_SCANCODE_A))
	{
		mCurrentAction = mActionMap["run"];
		mCurrentAction->setRightMove(false);
	}
	else if (InputManager::getInstance()->keyDown(SDL_SCANCODE_D))
	{
		mCurrentAction = mActionMap["run"];
		mCurrentAction->setRightMove(true);
	}
	else
	{
		mCurrentAction = nullptr;
	}
	
	if (mCurrentAction != nullptr)
	{
		mCurrentAction->setPos(mPosition.getX(), mPosition.getY());
		mCurrentAction->processData();
		mPosition = mCurrentAction->getPos();
	}
}

void PlayerObject::renderObject() const
{
	if (mCurrentAction == nullptr)
	{
		ObjectModel::renderObject();
	}
	else
	{
		mCurrentAction->renderObject();
	}
}

void PlayerObject::clearObject()
{

}
