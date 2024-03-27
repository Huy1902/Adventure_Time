#include "PlayerObject.h"

#include "GameManager.h"
#include "RunAction.h"
#include "JumpAction.h"

#include "InputManager.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "ObjectParser.h"
const int HURT_MOVE_BACK = 2;
const int MOVE_SPEED = 10;
const int GRAVITY = 2;
const int UP_FORCE = -20;
const int LANDING_TIME = 4;
const int HURT_TIME = 12;
const int DYING_TIME = 29;

const int COST_DASH = 5;
const int COST_ATTACK = 12;

const int STA_RECOVER_SPEED = 1;

PlayerObject::PlayerObject()
{

	ObjectParser::getInstance()->parserAction("MainCharacter.xml", mActions, mTextures);
	for (const auto& ite : mTextures)
	{
		TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	}

	mStatus.LUCK = 10;
	mStatus.STA = 200;

	animation = new Animation();

	mPosition = new GameVector(100, 100);
	mVelocity = new GameVector(0, 0);
	mAcceleration = new GameVector(0, 0);

	animation = new Animation();

	mCharHeight = 64;
	mCharWidth = 64;
	mCurrentAction = IDLE;
	mFlip = SDL_FLIP_NONE;
	animation->changeAnim("idle2", 4, mFlip);


	animation->setSize(100, 64);
	animation->setPosition(*mPosition);

	mLandingTime = LANDING_TIME;
	mDyingTime = mActions["dying"].numFrames * mActions["dying"].speed;
	mCountTimeHurt = 0;

	MaxStatus = mStatus;
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
	static double start_jump_at_y = 0;
	mVelocity->setX(0);
	m_bOnGround = onGround();
	m_bHeadStuck = headStuck();
	if (mStatus.isAlive == false)
	{
		--mDyingTime;
		mCurrentAction = DYING;
		completeUpdateMethod();
		return;
	}
	if (m_bHurting == true)
	{
		mCurrentAction = HURT;
		++mCountTimeHurt;
		if (mCountTimeHurt >= HURT_TIME)
		{
			m_bHurting = false;
			mStatus.isInvulnerable = false;
			mCountTimeHurt = 0;
		}
		if (isRight() == true)
		{
			mVelocity->setX(-HURT_MOVE_BACK);
		}
		else
		{
			mVelocity->setX(HURT_MOVE_BACK);
		}
		completeUpdateMethod();


		return;
	}
	if (mStatus.STA < MaxStatus.STA)
	{
		mStatus.STA += STA_RECOVER_SPEED;
	}
	if (m_bOnGround == true)
	{
		mVelocity->setY(0);
		mAcceleration->setY(0);
		if (mCurrentAction == FALL || (mCurrentAction == JUMP && start_jump_at_y < mPosition->getY()))
		{
			mCurrentAction = LANDING;
			mLandingTime = 0;
		}
		else
		{
			mCurrentAction = IDLE;
		}
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
		start_jump_at_y = mPosition->getY();
	}
	else
		if (m_bJump == false && m_bOnGround == false)
		{
			mCurrentAction = FALL;
		}
		else
			if (m_bHeadStuck == true && m_bOnGround == false)
			{
				mVelocity->setY(5);
			}
			else
				if (m_bJump == true)
				{
					mCurrentAction = JUMP;
				}
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_J) && m_bOnGround == true && mStatus.STA > COST_ATTACK * mActions["attack1"].numFrames * mActions["attack1"].speed && mCountTimeAttack1 == 0)
	{
		mCurrentAction = ATTACK1;
		mCountTimeAttack1 = mActions["attack1"].numFrames * mActions["attack1"].speed;
	}
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_I) && m_bOnGround == true)
	{
		mCurrentAction = CRIT;
		mCountTimeCrit = mActions["crit"].numFrames * mActions["crit"].speed;
	}
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_L) && m_bOnGround == true && mStatus.STA > COST_DASH * mActions["dash"].numFrames * mActions["dash"].speed && mCountTimeDash == 0)
	{
		if (InputManager::getInstance()->keyDown(SDL_SCANCODE_A))
		{
			mVelocity->setX(-MOVE_SPEED * 2);
			mFlip = SDL_FLIP_HORIZONTAL;
			mCurrentAction = DASH;
			mCountTimeDash = mActions["dash"].numFrames * mActions["dash"].speed;
		}
		if (InputManager::getInstance()->keyDown(SDL_SCANCODE_D))
		{
			mVelocity->setX(MOVE_SPEED * 2);
			mFlip = SDL_FLIP_NONE;
			mCurrentAction = DASH;
			mCountTimeDash = mActions["dash"].numFrames * mActions["dash"].speed;
		}
	}
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_U) && m_bOnGround == true && mCountTimeBash == 0)
	{
		mCurrentAction = BASH;
		mCountTimeBash = mActions["bash"].numFrames * mActions["bash"].speed;
	}

	if (mCountTimeBash > 0)
	{
		--mCountTimeBash;
		mCurrentAction = BASH;
		mVelocity->setX(0);
	}
	if (mCountTimeAttack1 > 0)
	{
		--mCountTimeAttack1;
		mCurrentAction = ATTACK1;
		mVelocity->setX(0);
	}
	if (mCountTimeCrit > 0)
	{
		--mCountTimeCrit;
		mCurrentAction = CRIT;
		mVelocity->setX(0);
	}

	if (mCountTimeDash > 0)
	{
		--mCountTimeDash;
		mCurrentAction = DASH;
		mVelocity->setX(mVelocity->getX() * 2);
	}

	if (sideStuck() == 1 && mVelocity->getX() < 0)
	{
		mVelocity->setX(0);
	}
	if (sideStuck() == 2 && mVelocity->getX() > 0)
	{
		mVelocity->setX(0);
	}

	if (mLandingTime < LANDING_TIME)
	{
		++mLandingTime;
		mCurrentAction = LANDING;
	}

	completeUpdateMethod();
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
		mStatus.STA -= COST_ATTACK;
		attack1();
		break;
	case PlayerObject::LANDING:
		landing();
		break;
	case PlayerObject::HURT:
		hurt();
		break;
	case PlayerObject::DASH:
		mStatus.STA -= COST_DASH;
		dash();
		break;
	case PlayerObject::DYING:
		dying();
		break;
	case PlayerObject::BASH:
		bash();
		break;
	case PlayerObject::CRIT:
		crit();
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
	TextureManager::getInstance()->clearFromTexture("walk2");
	TextureManager::getInstance()->clearFromTexture("jump2");
}
void PlayerObject::getHurt()
{
	if (mStatus.isInvulnerable == false)
	{
		mStatus.isInvulnerable = true;
	}
	if (mStatus.HP <= 0)
	{
		mStatus.isAlive = false;
	}
	else
	{
		m_bHurting = true;
	}
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


void PlayerObject::completeUpdateMethod()
{
	AnimationProcess();

	*mVelocity += *mAcceleration;
	*mPosition += *mVelocity;

	animation->setPosition(*mPosition);
}

