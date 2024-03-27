#include "BarrerKnight.h"

#include "TextureManager.h"
#include "GameManager.h"
#include "CollisionManager.h"

#include "ObjectParser.h"

const int MOVE_SPEED = 2;
const int GRAVITY = 4;
const int UP_FORCE = -20;
void BarrerKnight::getHurt()
{
	//std::
	// 
	//  << mStatus.HP << '\n';
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

BarrerKnight::BarrerKnight() :
	EnemyObject()
{

	ObjectParser::getInstance()->parserAction("BarerKnight.xml", mActions, mTextures);
	for (const auto& ite : mTextures)
	{
		TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	}

	animation = new Animation();


	mPosition = new GameVector(1400, 600);
	mVelocity = new GameVector(0, 0);
	mAcceleration = new GameVector(0, 0);
	mMapPosition = new GameVector(0, 0);

	mCharWidth = 40;

	mCurrentAction = IDLE;
	animation->setPosition(*mPosition);

	mTimeRun = 100;

	mStatus.HP = 200;

	mCountStamina = 0;

	animation->setSize(0, 0);

	mDyingTime = mActions["dying"].numFrames * mActions["dying"].speed;
	mWakeTime = mActions["wake"].numFrames * mActions["wake"].speed;

	MaxStatus = mStatus;

}
BarrerKnight::~BarrerKnight()
{
	for (const auto& ite : mTextures)
	{
		TextureManager::getInstance()->clearFromTexture(ite.textureID);
	}
}

void BarrerKnight::renderObject() const
{
	animation->setPosition(*mPosition - *mMapPosition);
	animation->draw();
}

void BarrerKnight::clearObject()
{

}

void BarrerKnight::processData()
{
	if (mStatus.isAlive == false)
	{
		mCurrentAction = DYING;
		--mDyingTime;
		AnimationProcess();
		return;
	}

	if (mCountTimeHit > 0)
	{
		mCurrentAction = HIT;
		--mCountTimeHit;
		mStatus.isInvulnerable = true;
		AnimationProcess();

		return;
	}

	if (mCountTimeAttack2 > 0)
	{
		mCurrentAction = ATTACK2;
		--mCountTimeAttack2;
		if (animation->getIndexFrame() == 4)
		{
			if (mFlip == SDL_FLIP_HORIZONTAL)
			{
				mVelocity->setX(-50);
			}
			else
			{
				mVelocity->setX(50);
			}
		}
		completeUpdateMethod();
		return;
	}

	static int count_run = 0;
	static bool right = true;
	mVelocity->setX(0);
	m_bOnGround = onGround();
	//m_bHeadStuck = headStuck();


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
			if (mCountStamina == mStatus.STA * 5)
			{
				mCurrentAction = ATTACK2;
				mCountStamina = 0;
				mCountTimeAttack2 = mActions["attack2"].numFrames * mActions["attack2"].speed;
			}
			else if (mCountStamina > mStatus.STA * 0)
			{
				mCurrentAction = ATTACK1;
				mCountTimeAttack1 = mActions["attack1"].numFrames * mActions["attack1"].speed;
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
			if (count_run == mTimeRun)
			{
				if (right == true)
				{
					right = false;
				}
				else
				{
					right = true;
				}
				count_run = 0;
			}
			++count_run;
			if (right == true)
			{
				mFlip = SDL_FLIP_NONE;
				mVelocity->setX(MOVE_SPEED);
			}
			else
			{
				mFlip = SDL_FLIP_HORIZONTAL;
				mVelocity->setX(-MOVE_SPEED);
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
	AnimationProcess();
	*mVelocity += *mAcceleration;
	*mPosition += *mVelocity;

	animation->setPosition(*mPosition);
}

void BarrerKnight::AnimationProcess()
{
	switch (mCurrentAction)
	{
	case BarrerKnight::RUN:
		run();
		break;
	case BarrerKnight::WAKE_UP:
		wake();
		break;
	case BarrerKnight::FALL:
		none();
		break;
	case BarrerKnight::IDLE:
		none();
		break;
	case BarrerKnight::ATTACK1:
		attack1();
		break;
	case BarrerKnight::HIT:
		hit();
		break;
	case BarrerKnight::ATTACK2:
		attack2();
		break;
	case BarrerKnight::DYING:
		dying();
		break;
	default:
		break;
	}
	animation->update();
}

bool BarrerKnight::onGround()
{
	return CollisionManager::getInstance()->checkEnemyOnGround(this);
}

void BarrerKnight::completeUpdateMethod()
{
	AnimationProcess();

	*mVelocity += *mAcceleration;
	*mPosition += *mVelocity;

	animation->setPosition(*mPosition);
}

