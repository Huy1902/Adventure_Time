#include "PlayerObject.h"

#include "GameManager.h"
#include "RunAction.h"
#include "JumpAction.h"

#include "InputManager.h"
#include "TextureManager.h"
#include "CollisionManager.h"

#include "Animation.h"

const int MOVE_SPEED = 10;
const int GRAVITY = 5;
const int UP_FORCE = -30;

PlayerObject::PlayerObject() :
	ObjectModel()
	//m_bOnAir(false)
{
	TextureManager::getInstance()->load("assets/knight_player/Walking_KG_1.png", "run", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/knight_player/Jump_KG_1.png", "jump", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/knight_player/Fall_KG_1.png", "fall", GameManager::getInstance()->getRenderer());
	mPosition = new GameVector();
	mVelocity = new GameVector(0, 0);
	mAcceleration = new GameVector(0, 0);

	mCharHeight = 64;
	mCharWidth = 100;
	mCurrentAction = IDLE;
	mBackAction = IDLE;
	mFlip = SDL_FLIP_NONE;
	Animation::getInstance()->changeAnim("idle", 4, mFlip);


	Animation::getInstance()->setSize(100, 64);
	Animation::getInstance()->setPosition({ 0, 100 });

	m_bOnGround = true;
}

PlayerObject::~PlayerObject()
{

}

void PlayerObject::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	ObjectModel::loadTexture(std::move(Info));
	//RunAction* walk = new RunAction();
	//walk->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("walk", (int)mPosition->getX(), (int)mPosition->getY(), 100, 64, 7, 1.0)));
	//mActionMap["walk"] = walk;

	//JumpAction* jump = new JumpAction();
	//jump->loadTexture(std::unique_ptr<TextureLoader>(new TextureLoader("jump", (int)mPosition->getX(), (int)mPosition->getY(), 100, 64, 6, 1.0)));
	//mActionMap["jump"] = jump;
	//mCurrentAction = mActionMap["jump"];
}

void PlayerObject::processData()
{
	//if (onGround() == false || m_bOnAir == true)
	//{
	//	if (mCurrentAction == nullptr)
	//	{
	//		while (onGround() == false)
	//		{
	//			mPosition->setX(mPosition->getX() - 1);
	//		}
	//	}
	//	else
	//	{
	//		mAcceleration->setY(10);
	//		if (InputManager::getInstance()->keyDown(SDL_SCANCODE_A))
	//		{
	//			mVelocity->setX(-MOVE_SPEED);
	//			m_bRight = false;
	//			mCurrentAction->setRightMove(m_bRight);
	//		}
	//		else if (InputManager::getInstance()->keyDown(SDL_SCANCODE_D))
	//		{
	//			mVelocity->setX(MOVE_SPEED);
	//			m_bRight = true;
	//			mCurrentAction->setRightMove(m_bRight);
	//		}
	//		else
	//		{
	//			mVelocity->setX(0);
	//		}
	//		if (mCurrentAction->isOnAir() == false)
	//		{
	//			m_bOnAir = false;
	//			mVelocity->setY(0);
	//			*mAcceleration = { 0, 0 };
	//			mCurrentAction = nullptr;
	//		}
	//		else
	//		{
	//			mAcceleration->setY(10);
	//			*mVelocity += *mAcceleration;
	//			*mPosition += *mVelocity;
	//			mCurrentAction->setPos(*mPosition);
	//			mCurrentAction->processData();
	//			mPosition = mCurrentAction->getPos();
	//		}
	//	}
	//}
	//else
	//{
	//	mAcceleration->setY(0);
	//	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_SPACE))
	//	{
	//		mCurrentAction = mActionMap["jump"];
	//		m_bOnAir = true;
	//		mCurrentAction->setPos(*mPosition);
	//		mCurrentAction->processData();
	//		mVelocity->setY(-50);
	//		mAcceleration->setY(10);
	//	}
	//	else if (InputManager::getInstance()->keyDown(SDL_SCANCODE_A))
	//	{
	//		mVelocity->setX(-MOVE_SPEED);
	//		mCurrentAction = mActionMap["walk"];
	//		m_bRight = false;
	//		mCurrentAction->setRightMove(m_bRight);
	//	}
	//	else if (InputManager::getInstance()->keyDown(SDL_SCANCODE_D))
	//	{
	//		mCurrentAction = mActionMap["walk"];
	//		mVelocity->setX(MOVE_SPEED);
	//		m_bRight = true;
	//		mCurrentAction->setRightMove(m_bRight);
	//	}
	//	else
	//	{
	//		mVelocity->setX(0);
	//		mCurrentAction = nullptr;
	//		ObjectModel::processData();
	//	}
	//	if (mCurrentAction != nullptr && m_bOnAir == false)
	//	{
	//		*mVelocity += *mAcceleration;
	//		*mPosition += *mVelocity;
	//		mCurrentAction->setPos(*mPosition);
	//		mCurrentAction->processData();
	//		mPosition = mCurrentAction->getPos();
	//	}
	//}
	mVelocity->setX(0);
	m_bOnGround = onGround();
	m_bHeadStuck = headStuck();


	if (m_bOnGround == true)
	{
		mVelocity->setY(0);
		mAcceleration->setY(0);
		mCurrentAction = IDLE;
		m_bJump = false;
	}
	else
	{
		mAcceleration->setY(GRAVITY);
	}

	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_A) == true)
	{
		mVelocity->setX(-MOVE_SPEED);
		mFlip = SDL_FLIP_HORIZONTAL;
		mCurrentAction = RUN;
	}
	else if (InputManager::getInstance()->keyDown(SDL_SCANCODE_D) == true)
	{
		mVelocity->setX(MOVE_SPEED);
		mFlip = SDL_FLIP_NONE;
		mCurrentAction = RUN;
	}

	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_K) && m_bOnGround == true && m_bHeadStuck == false)
	{
		m_bOnGround = false;
		m_bJump = true;
		mCurrentAction = JUMP;
		mVelocity->setY(UP_FORCE);
	}
	else
		if (m_bJump == false && m_bOnGround == false)
		{
			mCurrentAction = FALL;
		}
		else
			if (m_bHeadStuck == true && m_bOnGround == false)
			{
				mVelocity->setY(0);
			}
			else
				if (m_bJump == true)
				{
					mCurrentAction = JUMP;
				}

	if (sideStuck() == 1 && mVelocity->getX() < 0)
	{
		mVelocity->setX(0);
	}
	if (sideStuck() == 2 && mVelocity->getX() > 0)
	{
		mVelocity->setX(0);
	}

	AnimationProcess();

	*mVelocity += *mAcceleration;
	*mPosition += *mVelocity;

	Animation::getInstance()->setPosition(*mPosition);
}

void PlayerObject::AnimationProcess()
{
	switch (mCurrentAction)
	{
	case PlayerObject::RUN:
		Animation::getInstance()->changeAnim("run", 7, mFlip);
		break;
	case PlayerObject::JUMP:
		Animation::getInstance()->changeAnim("jump", 6, mFlip);
		Animation::getInstance()->setSpeed(4);
		break;
	case PlayerObject::IDLE:
		Animation::getInstance()->changeAnim("idle", 4, mFlip);
		break;
	case PlayerObject::FALL:
		Animation::getInstance()->changeAnim("fall", 3, mFlip);
		break;
	default:
		break;
	}
	Animation::getInstance()->update();
}

void PlayerObject::renderObject() const
{
	//if (mCurrentAction == nullptr)
	//{
	//	ObjectModel::renderObject();
	//}
	//else
	//{
	//	mCurrentAction->renderObject();
	//}
	Animation::getInstance()->draw();
}

void PlayerObject::clearObject()
{
	TextureManager::getInstance()->clearFromTexture("walk");
	TextureManager::getInstance()->clearFromTexture("jump");
}

bool PlayerObject::onGround()
{
	return CollisionManager::getInstance()->checkPlayerOnGround();
}

bool PlayerObject::headStuck()
{
	if (mFlip == SDL_FLIP_NONE)
	{
		return CollisionManager::getInstance()->checkPlayerHeadStuck(true);
	}
	return CollisionManager::getInstance()->checkPlayerHeadStuck(false);
}

int PlayerObject::sideStuck()
{
	if (CollisionManager::getInstance()->checkPlayerSideLeft() == true)
	{
		return 1;
	}
	else
		if (CollisionManager::getInstance()->checkPlayerSideRight() == true)
		{
			return 2;
		}
	return 0;
}
