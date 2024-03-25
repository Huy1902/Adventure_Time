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
const int DASH_TIME = 12;
const int HURT_TIME = 12;
const int DYING_TIME = 29;

PlayerObject::PlayerObject() :
	ObjectModel()
	//m_bOnAir(false)
{
	//TextureManager::getInstance()->load("assets/knight_player/Walking_KG_2.png", "run2", GameManager::getInstance()->getRenderer());
	//TextureManager::getInstance()->load("assets/knight_player/Jump_KG_2.png", "jump2", GameManager::getInstance()->getRenderer());
	//TextureManager::getInstance()->load("assets/knight_player/Fall_KG_2.png", "fall2", GameManager::getInstance()->getRenderer());
	//TextureManager::getInstance()->load("assets/knight_player/Attack_KG_1.png", "attack1", GameManager::getInstance()->getRenderer());
	//TextureManager::getInstance()->load("assets/knight_player/Hurt_KG_2.png", "hurt2", GameManager::getInstance()->getRenderer());
	//TextureManager::getInstance()->load("assets/knight_player/Landing_KG_2.png", "landing2", GameManager::getInstance()->getRenderer());
	//TextureManager::getInstance()->load("assets/knight_player/Idle_KG_2.png", "idle2", GameManager::getInstance()->getRenderer());
	//TextureManager::getInstance()->load("assets/knight_player/Dashing_KG_2.png", "dash2", GameManager::getInstance()->getRenderer());
	//TextureManager::getInstance()->load("assets/knight_player/Dying_KG_2.png", "dying2", GameManager::getInstance()->getRenderer());

	ObjectParser::getInstance()->parserAction("MainCharacter.xml", mActions, mTextures);
	for (const auto& ite : mTextures)
	{
		TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	}

	mStatus.LUCK = 100;

	animation = new Animation();

	mPosition = new GameVector(100, 100);
	mVelocity = new GameVector(0, 0);
	mAcceleration = new GameVector(0, 0);

	animation = new Animation();

	mCharHeight = 64;
	mCharWidth = 64;
	mCurrentAction = IDLE;
	mBackAction = IDLE;
	mFlip = SDL_FLIP_NONE;
	animation->changeAnim("idle2", 4, mFlip);


	animation->setSize(100, 64);
	animation->setPosition(*mPosition);


	m_bAttack = false;
	mLandingTime = LANDING_TIME;
	mTimeDash = DASH_TIME;
	mCountTimeDying = DYING_TIME;
	mCountTimeHurt = 0;
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
		--mCountTimeDying;
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
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_J) && m_bOnGround == true)
	{
		mVelocity->setX(0);
		mCurrentAction = ATTACK1;
		++mTimeAttack;
	}
	else
	{
		mTimeAttack = 0;
	}
	if (InputManager::getInstance()->keyDown(SDL_SCANCODE_L) && m_bOnGround == true && mCooldownDash <= 0)
	{
		if (InputManager::getInstance()->keyDown(SDL_SCANCODE_A))
		{
			mVelocity->setX(-MOVE_SPEED * 2);
			mFlip = SDL_FLIP_HORIZONTAL;
			mCurrentAction = DASH;
			mTimeDash = 0;
			mCooldownDash = 20;
		}
		if (InputManager::getInstance()->keyDown(SDL_SCANCODE_D))
		{
			mVelocity->setX(MOVE_SPEED * 2);
			mFlip = SDL_FLIP_NONE;
			mCurrentAction = DASH;
			mTimeDash = 0;
			mCooldownDash = 20;
		}
	}
	--mCooldownDash;

	if (mTimeDash < DASH_TIME)
	{
		++mTimeDash;
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
		attack1();
		break;
	case PlayerObject::LANDING:
		landing();
		break;
	case PlayerObject::HURT:
		hurt();
		break;
	case PlayerObject::DASH:
		dash();
		break;
	case PlayerObject::DYING:
		dying();
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

void PlayerObject::run()
{
	Info temp = mActions["run"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
	/*animation->changeAnim("barrer_run", 7, mFlip);
	animation->setSize(59, 64);*/
}
//void PlayerObject::run()
//{
//	animation->changeAnim("run2", 7, mFlip);
//}

void PlayerObject::jump()
{
	Info temp = mActions["jump"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void PlayerObject::idle()
{
	Info temp = mActions["idle"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void PlayerObject::fall()
{
	Info temp = mActions["fall"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void PlayerObject::attack1()
{
	Info temp = mActions["attack1"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void PlayerObject::hurt()
{
	Info temp = mActions["hurt"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void PlayerObject::landing()
{
	Info temp = mActions["landing"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void PlayerObject::dash()
{
	Info temp = mActions["dash"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void PlayerObject::dying()
{
	Info temp = mActions["dying"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void PlayerObject::completeUpdateMethod()
{
	AnimationProcess();

	*mVelocity += *mAcceleration;
	*mPosition += *mVelocity;

	animation->setPosition(*mPosition);
}

