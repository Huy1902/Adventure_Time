#include "PlayerObject.h"

#include "GameManager.h"
#include "RunAction.h"
#include "JumpAction.h"
#include "InputManager.h"

PlayerObject::PlayerObject() :
	ObjectModel(),
	m_bOnAir(false)
{
	RunAction* walk = new RunAction();
	walk->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("walk", mPosition.getX(), mPosition.getY(), 100, 64, 7, 1.0)));
	mActionMap["walk"] = walk;

	JumpAction* jump = new JumpAction();
	jump->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("jump", mPosition.getX(), mPosition.getY(), 100, 64, 6, 1.0)));
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
	if (m_bOnAir == true)
	{
		if (InputManager::getInstance()->keyDown(SDL_SCANCODE_A))
		{
			mVelocity.setX(-15);
			mCurrentAction->setRightMove(false);
		}
		else if (InputManager::getInstance()->keyDown(SDL_SCANCODE_D))
		{
			mVelocity.setX(15);
			mCurrentAction->setRightMove(true);
		}
		else
		{
			mVelocity.setX(0);
		}
		if (mCurrentAction->isOnAir() == false)
		{
			m_bOnAir = false;
			mVelocity.setY(0);
			mAcceleration = { 0, 0 };
		}
		else
		{
			mVelocity += mAcceleration;
			mPosition += mVelocity;
			mCurrentAction->setPos(mPosition.getX(), mPosition.getY());
			mCurrentAction->processData();
			mPosition = mCurrentAction->getPos();
		}
	}
	else
	{
		if (InputManager::getInstance()->keyDown(SDL_SCANCODE_SPACE))
		{
			mCurrentAction = mActionMap["jump"];
			m_bOnAir = true;
			mCurrentAction->setPos(mPosition.getX(), mPosition.getY());
			mCurrentAction->processData();
			mVelocity.setY(-50);
			mAcceleration.setY(10);
		}
		else if (InputManager::getInstance()->keyDown(SDL_SCANCODE_A))
		{
			mVelocity.setX(-15);
			mCurrentAction = mActionMap["walk"];
			mCurrentAction->setRightMove(false);
		}
		else if (InputManager::getInstance()->keyDown(SDL_SCANCODE_D))
		{
			mCurrentAction = mActionMap["walk"];
			mVelocity.setX(15);
			mCurrentAction->setRightMove(true);
		}
		else
		{
			mCurrentAction = nullptr;
			ObjectModel::processData();
		}
		if (mCurrentAction != nullptr && m_bOnAir == false)
		{
			mVelocity += mAcceleration;
			mPosition += mVelocity;
			mCurrentAction->setPos(mPosition.getX(), mPosition.getY());
			mCurrentAction->processData();
			mPosition = mCurrentAction->getPos();
		}
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
