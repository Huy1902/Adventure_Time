#include "PlayerObject.h"

#include "GameManager.h"
#include "RunAction.h"
#include "JumpAction.h"

#include "InputManager.h"
#include "TextureManager.h"
#include "CollisionManager.h"

const int MOVE_SPEED = 10;
const int GRAVITY = 2;
const int UP_FORCE = -20;

PlayerObject::PlayerObject() :
	ObjectModel()
	//m_bOnAir(false)
{
	TextureManager::getInstance()->load("assets/knight_player/Walking_KG_1.png", "run", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/knight_player/Jump_KG_1.png", "jump", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/knight_player/Fall_KG_1.png", "fall", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/knight_player/Attack_KG_1.png", "attack1", GameManager::getInstance()->getRenderer());

	mPosition = new GameVector();
	mVelocity = new GameVector(0, 0);
	mAcceleration = new GameVector(0, 0);

	animation = new Animation();

	mCharHeight = 64;
	mCharWidth = 100;
	mCurrentAction = IDLE;
	mBackAction = IDLE;
	mFlip = SDL_FLIP_NONE;
	animation->changeAnim("idle", 4, mFlip);


	animation->setSize(100, 64);
	animation->setPosition({ 0, 100 });

	m_bAttack = false;
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
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_J) && m_bOnGround == true)
	{
		mVelocity->setX(0);
		mCurrentAction = ATTACK1;
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

	animation->setPosition(*mPosition);
}

void PlayerObject::AnimationProcess()
{
	switch (mCurrentAction)
	{
	case PlayerObject::RUN:
		run();
		break;
	case PlayerObject::JUMP:
		jump();
		break;
	case PlayerObject::IDLE:
		idle();
		break;
	case PlayerObject::FALL:
		fall();
		break;
	case PlayerObject::ATTACK1:
		attack1();
		break;
	default:
		break;
	}
	animation->update();
}

void PlayerObject::renderObject() const
{
	animation->draw();
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

void PlayerObject::run()
{
	animation->changeAnim("run", 7, mFlip);
}

void PlayerObject::jump()
{
	animation->changeAnim("jump", 6, mFlip);
	animation->setSpeed(4);
}

void PlayerObject::idle()
{
	animation->changeAnim("idle", 4, mFlip);
}

void PlayerObject::fall()
{
	animation->changeAnim("fall", 3, mFlip);
}

void PlayerObject::attack1()
{
	animation->changeAnim("attack1", 6, mFlip);
}
