#include "Archer.h"


#include "TextureManager.h"
#include "GameManager.h"
#include "CollisionManager.h"

#include "ObjectParser.h"

#include "ArrowManager.h"

const int MOVE_SPEED = 2;
const int GRAVITY = 4;
const int UP_FORCE = -20;
const int TIME_RUN = 100;
const int ARROW_POS_X = 200;
const int ARROW_POS_Y = 30;
void Archer::getHurt()
{
	if (mStatus.isInvulnerable == false)
	{
		mCountTimeHit = mActions["hit"].numFrames * mActions["hit"].speed;
	}

	if (mStatus.HP <= 0)
	{
		mStatus.isAlive = false;
		mPosition->setX(mPosition->getX() + animation->getWidth() / 2 - mActions["dying"].w / 2);
		/*animation->setPosition({ m});*/
	}
}

Archer::Archer() :
	EnemyObject()
{

	ObjectParser::getInstance()->parserAction("archer.xml", mActions);

	animation = new Animation();


	mPosition = new GameVector();
	mVelocity = new GameVector(0, 0);
	mAcceleration = new GameVector(0, 0);
	mMapPosition = new GameVector(0, 0);

	mCurrentAction = IDLE;
	animation->setPosition(*mPosition);

	mStatus.HP = 200;

	mCountStamina = 0;

	mDyingTime = mActions["dying"].numFrames * mActions["dying"].speed - 1;
	mWakeTime = mActions["idle"].numFrames * mActions["idle"].speed - 1;


	animation->setSize(0, 0);

	mCharWidth = 40;

	MaxStatus = mStatus;

}
Archer::~Archer()
{

}

void Archer::renderObject() const
{
	animation->setPosition(*mPosition - *mMapPosition);
	animation->draw();
}

void Archer::clearObject()
{
	for (const auto& ite : mTextures)
	{
		TextureManager::getInstance()->clearFromTexture(ite.textureID);
	}
}

void Archer::processData()
{
	if (mStatus.isAlive == false)
	{
		mCurrentAction = DYING;
		--mDyingTime;
		AnimationProcess();
		return;
	}
	else
	{
		mStatus.isStunned = false;
	}
	if (mStatus.isStunned = true)
	{
		if (mCountTimeStun > 0)
		{
			--mCountTimeStun;
			mCurrentAction = STUN;
			AnimationProcess();
			return;
		}
		else
		{
			mStatus.isStunned = false;
		}
	}
	else
	{
		mCountTimeStun = 0;
	}

	if (mCountTimeHit > 0)
	{
		mCurrentAction = HIT;
		--mCountTimeHit;
		mStatus.isInvulnerable = true;
		AnimationProcess();

		return;
	}

	if (mCountTimeAttack1 > 0)
	{
		--mCountTimeAttack1;
		mCurrentAction = ATTACK1;
		completeUpdateMethod();
		return;
	}

	static bool right = true;
	mVelocity->setX(0);
	m_bOnGround = onGround();
	if (m_bOnGround == true)
	{
		mVelocity->setY(0);
		mAcceleration->setY(0);
		mCurrentAction = IDLE;
	}
	else
	{
		mAcceleration->setY(GRAVITY);
		mCurrentAction = FALL;
	}
	if (m_bOnGround == true)
	{
		mCurrentAction = RUN;
		if (CollisionManager::getInstance()->checkEnemyNearPlayer(this) <= 600)
		{

			if (CollisionManager::getInstance()->checkPlayerIsRightSideWithEnemy(this) == false)
			{
				mFlip = SDL_FLIP_HORIZONTAL;
				if (CollisionManager::getInstance()->checkEnemyNearPlayer(this) >= 200)
				{
					mVelocity->setX(-MOVE_SPEED * 2);
				}
			}
			else 
			{
				mFlip = SDL_FLIP_NONE;
				if (CollisionManager::getInstance()->checkEnemyNearPlayer(this) >= 200 + animation->getWidth())
				{
					mVelocity->setX(MOVE_SPEED * 2);
				}
			}

			if (mCountStamina == mStatus.STA * 1)
			{
				mCountStamina = 0;
				mCurrentAction = ATTACK1;
				mCountTimeAttack1 = (mActions["attack1"].numFrames * mActions["attack1"].speed);
				if (mFlip == SDL_FLIP_HORIZONTAL)
				{
					ArrowManager::getInstance()->addEnemyArrow(GameVector(mPosition->getX() + animation->getWidth() - ARROW_POS_X, mPosition->getY() + ARROW_POS_Y), *mMapPosition, false);
				}
				else
				{
					ArrowManager::getInstance()->addEnemyArrow(GameVector(mPosition->getX() + ARROW_POS_X, mPosition->getY() + ARROW_POS_Y), *mMapPosition, true);
				}
			}
			++mCountStamina;


		}
		else
		{
			//mAttack1Time = 0;
			if (mCountTimeRun == 0)
			{
				mCountTimeRun = TIME_RUN;
				if (mFlip == SDL_FLIP_NONE)
				{
					mFlip = SDL_FLIP_HORIZONTAL;
					mVelocity->setX(-MOVE_SPEED);
				}
				else
				{
					mFlip = SDL_FLIP_NONE;
					mVelocity->setX(MOVE_SPEED);
				}
			}
		}
	}
	if (sideStuck(this) == true)
	{
		mVelocity->setX(0);
	}
	if (m_bSleep == true)
	{
		mCountStamina = 0;
		mCurrentAction = IDLE;
		mVelocity->setX(0);
		if (CollisionManager::getInstance()->checkEnemyNearPlayer(this) <= 300)
		{
			m_bSleep = false;
		}
	}
	else
	{
		mStatus.isInvulnerable = false;
		if (mWakeTime > 0)
		{
			mCountStamina = 0;
			mCurrentAction = WAKE_UP;
			--mWakeTime;
			mStatus.isInvulnerable = true;
		}
	}
	completeUpdateMethod();
}

void Archer::AnimationProcess()
{
	switch (mCurrentAction)
	{
	case Archer::RUN:
		run();
		break;
	case Archer::WAKE_UP:
		idle();
		break;
	case Archer::FALL:
		fall();
		break;
	case Archer::IDLE:
		idle();
		break;
	case Archer::ATTACK1:
		attack1();
		break;
	case Archer::HIT:
		hit();
		break;
	case Archer::DYING:
		dying();
		break;
	default:
		break;
	}
	animation->update();
}

bool Archer::onGround()
{
	return CollisionManager::getInstance()->checkEnemyOnGround(this);
}

void Archer::completeUpdateMethod()
{
	AnimationProcess();

	*mVelocity += *mAcceleration;
	*mPosition += *mVelocity;

	animation->setPosition(*mPosition);
}