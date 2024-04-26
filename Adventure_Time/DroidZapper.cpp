#include "DroidZapper.h"



#include "TextureManager.h"
#include "GameManager.h"
#include "CollisionManager.h"

#include "ObjectParser.h"

const int MOVE_SPEED = 2;
const int GRAVITY = 4;
const int UP_FORCE = -20;
const int TIME_RUN = 100;

void DroidZapper::getHurt()
{
	if (mStatus.isInvulnerable == false)
	{
		mCountTimeHit = mActions["hit"].numFrames * mActions["hit"].speed;
	}

	if (mStatus.HP <= 0)
	{
		mStatus.isAlive = false;
		mPosition->setX(mPosition->getX() + mAnimation->getWidth() / 2 - mActions["dying"].w / 2);
		/*mAnimation->setPosition({ m});*/
	}
}

DroidZapper::DroidZapper() :
	EnemyObject()
{

	ObjectParser::getInstance()->parserAction("droid_zapper.xml", mActions);

	//animation = new Animation();


	//mPosition = new GameVector();
	//mVelocity = new GameVector(0, 0);
	//mAcceleration = new GameVector(0, 0);
	//mMapPosition = new GameVector(0, 0);

	mCurrentAction = IDLE;
	mAnimation->setPosition(*mPosition);

	mStatus.HP = 200;

	mCountStamina = 0;

	mDyingTime = mActions["dying"].numFrames * mActions["dying"].speed - 1;
	mWakeTime = mActions["wake"].numFrames * mActions["wake"].speed - 1;


	mAnimation->setSize(0, 0);

	mCharWidth = 40;

	mMaxStatus = mStatus;

}
DroidZapper::~DroidZapper()
{

}

void DroidZapper::renderObject() const
{
	mAnimation->setPosition(*mPosition - *mMapPosition);
	mAnimation->draw();
}

void DroidZapper::clearObject()
{
	for (const auto& ite : mTextures)
	{
		TextureManager::getInstance()->clearFromTexture(ite.textureID);
	}
}

void DroidZapper::processData()
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
		if (CollisionManager::getInstance()->checkEnemyNearPlayer(this) <= 400)
		{
			if (mCountStamina == mStatus.STA * 1)
			{
				mCountStamina = 0;
				mCurrentAction = ATTACK1;
				mCountTimeAttack1 = (mActions["attack1"].numFrames * mActions["attack1"].speed);
			}
			++mCountStamina;

			if (CollisionManager::getInstance()->checkPlayerIsRightSideWithEnemy(this) == false)
			{
				mFlip = SDL_FLIP_HORIZONTAL;
				mVelocity->setX(-MOVE_SPEED * 2);
			}
			else
			{
				mFlip = SDL_FLIP_NONE;
				mVelocity->setX(MOVE_SPEED * 2);
			}

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
		if (CollisionManager::getInstance()->checkEnemyNearPlayer(this) <= 100)
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

void DroidZapper::AnimationProcess()
{
	switch (mCurrentAction)
	{
	case DroidZapper::RUN:
		run();
		break;
	case DroidZapper::WAKE_UP:
		wake();
		break;
	case DroidZapper::FALL:
		none();
		break;
	case DroidZapper::IDLE:
		none();
		break;
	case DroidZapper::ATTACK1:
		attack1();
		break;
	case DroidZapper::HIT:
		hit();
		break;
	case DroidZapper::DYING:
		dying();
		break;
	default:
		break;
	}
	mAnimation->update();
}

bool DroidZapper::onGround()
{
	return CollisionManager::getInstance()->checkEnemyOnGround(this);
}

void DroidZapper::completeUpdateMethod()
{
	AnimationProcess();

	*mVelocity += *mAcceleration;
	*mPosition += *mVelocity;

	mAnimation->setPosition(*mPosition);
}