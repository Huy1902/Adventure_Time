#include "Vagabond.h"
#include "TextureManager.h"
#include "GameManager.h"
#include "CollisionManager.h"

#include "ObjectParser.h"

const int MOVE_SPEED = 2;
const int GRAVITY = 4;
const int UP_FORCE = -20;
const int TIME_RUN = 100;
void Vagabond::getHurt()
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

Vagabond::Vagabond() :
	EnemyObject()
{
	ObjectParser::getInstance()->parserTexture("vagabond.xml", mTextures);
	for (auto& ite : mTextures)
	{
		TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	}
	ObjectParser::getInstance()->parserAction("vagabond.xml", mActions);

	animation = new Animation();


	mPosition = new GameVector();
	mVelocity = new GameVector(0, 0);
	mAcceleration = new GameVector(0, 0);
	mMapPosition = new GameVector(0, 0);

	mCharWidth = 40;

	mCurrentAction = IDLE;
	animation->setPosition(*mPosition);
	mStatus.HP = 200;

	mCountStamina = 0;

	animation->setSize(0, 0);

	mDyingTime = mActions["dying"].numFrames * mActions["dying"].speed - 1;
	mWakeTime = mActions["wake"].numFrames * mActions["wake"].speed - 1;

	MaxStatus = mStatus;

}
Vagabond::~Vagabond()
{
	for (auto& ite : mTextures)
	{
		TextureManager::getInstance()->clearFromTexture(ite.textureID);
	}
}

void Vagabond::renderObject() const
{
	animation->setPosition(*mPosition - *mMapPosition);
	animation->draw();
}

void Vagabond::clearObject()
{
	for (const auto& ite : mTextures)
	{
		TextureManager::getInstance()->clearFromTexture(ite.textureID);
	}
}

void Vagabond::processData()
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
			if (mCountStamina == mStatus.STA * 3)
			{
				mCountStamina = 0;
				mCurrentAction = ATTACK2;
				mCountTimeAttack2 = mActions["attack2"].numFrames * mActions["attack2"].speed;
			}
			else if (mCountStamina == mStatus.STA * 1 || mCountStamina == mStatus.STA * 2)
			{
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
			else
			{
				--mCountTimeRun;
				if (mFlip == SDL_FLIP_NONE)
				{
					mVelocity->setX(MOVE_SPEED);
				}
				else
				{
					mVelocity->setX(-MOVE_SPEED);
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

void Vagabond::AnimationProcess()
{
	switch (mCurrentAction)
	{
	case Vagabond::RUN:
		run();
		break;
	case Vagabond::WAKE_UP:
		wake();
		break;
	case Vagabond::FALL:
		none();
		break;
	case Vagabond::IDLE:
		none();
		break;
	case Vagabond::ATTACK1:
		attack1();
		break;
	case Vagabond::HIT:
		hit();
		break;
	case Vagabond::ATTACK2:
		attack2();
		break;
	case Vagabond::DYING:
		dying();
		break;
	case Vagabond::STUN:
		stun();
		break;
	default:
		break;
	}
	animation->update();
}

bool Vagabond::onGround()
{
	return CollisionManager::getInstance()->checkEnemyOnGround(this);
}

void Vagabond::completeUpdateMethod()
{
	AnimationProcess();

	*mVelocity += *mAcceleration;
	*mPosition += *mVelocity;

	animation->setPosition(*mPosition);
}

