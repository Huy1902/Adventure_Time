#include "PlayerObject.h"

#include "GameManager.h"
#include "RunAction.h"
#include "JumpAction.h"
#include "InputManager.h"

#include "TextureManager.h"

const int MOVE_SPEED = 10;

PlayerObject::PlayerObject() :
	ObjectModel(),
	m_bOnAir(false)
{
	TextureManager::getInstance()->load("assets/knight_player/Walking_KG_1.png", "walk", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/knight_player/Jump_KG_1.png", "jump", GameManager::getInstance()->getRenderer());
	mVelocity = new GameVector();
	mPosition = new GameVector();
	mAcceleration = new GameVector();

}

PlayerObject::~PlayerObject()
{

}

void PlayerObject::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	ObjectModel::loadTexture(std::move(Info));
	RunAction* walk = new RunAction();
	walk->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("walk", (int)mPosition->getX(), (int)mPosition->getY(), 100, 64, 7, 1.0)));
	mActionMap["walk"] = walk;

	JumpAction* jump = new JumpAction();
	jump->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("jump", (int)mPosition->getX(), (int)mPosition->getY(), 100, 64, 6, 1.0)));
	mActionMap["jump"] = jump;
	mCurrentAction = mActionMap["jump"];
}

void PlayerObject::processData()
{
	if (m_bOnAir == true)
	{
		if (InputManager::getInstance()->keyDown(SDL_SCANCODE_A))
		{
			mVelocity->setX(-MOVE_SPEED);
			m_bRight = false;
			mCurrentAction->setRightMove(m_bRight);
		}
		else if (InputManager::getInstance()->keyDown(SDL_SCANCODE_D))
		{
			mVelocity->setX(MOVE_SPEED);
			m_bRight = true;
			mCurrentAction->setRightMove(m_bRight);
		}
		else
		{
			mVelocity->setX(0);
		}
		if (mCurrentAction->isOnAir() == false)
		{
			m_bOnAir = false;
			mVelocity->setY(0);
			*mAcceleration = { 0, 0 };
			mCurrentAction = nullptr;
		}
		else
		{
			*mVelocity += *mAcceleration;
			*mPosition += *mVelocity;
			mCurrentAction->setPos(*mPosition);
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
			mCurrentAction->setPos(*mPosition);
			mCurrentAction->processData();
			mVelocity->setY(-50);
			mAcceleration->setY(10);
		}
		else if (InputManager::getInstance()->keyDown(SDL_SCANCODE_A))
		{
			mVelocity->setX(-MOVE_SPEED);
			mCurrentAction = mActionMap["walk"];
			m_bRight = false;
			mCurrentAction->setRightMove(m_bRight);
		}
		else if (InputManager::getInstance()->keyDown(SDL_SCANCODE_D))
		{
			mCurrentAction = mActionMap["walk"];
			mVelocity->setX(MOVE_SPEED);
			m_bRight = true;
			mCurrentAction->setRightMove(m_bRight);
		}
		else
		{
			mVelocity->setX(0);
			mCurrentAction = nullptr;
			ObjectModel::processData();
		}
		if (mCurrentAction != nullptr && m_bOnAir == false)
		{
			*mVelocity += *mAcceleration;
			*mPosition += *mVelocity;
			mCurrentAction->setPos(*mPosition);
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
	TextureManager::getInstance()->clearFromTexture("walk");
	TextureManager::getInstance()->clearFromTexture("jump");
}
