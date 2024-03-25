#include "DroidZapper.h"



#include "TextureManager.h"
#include "GameManager.h"
#include "CollisionManager.h"

#include "ObjectParser.h"

const int MOVE_SPEED = 2;
const int GRAVITY = 4;
const int UP_FORCE = -20;

void DroidZapper::getHurt()
{
	//std::cout << mStatus.HP << '\n';
	if (mStatus.isInvulnerable == false)
	{
		m_bHit = true;
	}

	if (mStatus.HP <= 0)
	{
		mStatus.isAlive = false;
	}
}

DroidZapper::DroidZapper() :
	EnemyObject()
{
	/*TextureManager::getInstance()->load("assets/barrel_knight/run.png", "barrer_run", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/barrel_knight/wake.png", "barrer_wake", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/barrel_knight/none.png", "barrer_none", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/barrel_knight/attack1.png", "barrer_attack1", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/barrel_knight/hit.png", "barrer_hit", GameManager::getInstance()->getRenderer());*/

	ObjectParser::getInstance()->parserAction("droid_zapper.xml", mActions, mTextures);
	for (const auto& ite : mTextures)
	{
		TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	}

	animation = new Animation();


	mPosition = new GameVector(1200, 600);
	mVelocity = new GameVector(0, 0);
	mAcceleration = new GameVector(0, 0);
	mMapPosition = new GameVector(0, 0);

	mCurrentAction = IDLE;
	animation->setPosition(*mPosition);

	mTimeRun = 100;

	mStatus.HP = 200;

	mCountHitTime = 0;

	mCountStamina = 0;

	HIT_TIME = mActions["hit"].numFrames * mActions["hit"].speed;

	mDyingTime = mActions["dying"].numFrames * mActions["dying"].speed;

	animation->setSize(0, 0);

	mCharWidth = 40;

}
DroidZapper::~DroidZapper()
{
	for (const auto& ite : mTextures)
	{
		TextureManager::getInstance()->clearFromTexture(ite.textureID);
	}
}

//void DroidZapper::loadTexture(std::unique_ptr<TextureLoader> Info)
//{
//	ObjectModel::loadTexture(std::move(Info));
//}
void DroidZapper::renderObject() const
{
	animation->setPosition(*mPosition - *mMapPosition);
	animation->draw();
}

void DroidZapper::clearObject()
{

}

void DroidZapper::processData()
{
	if (mStatus.isAlive == false)
	{
		mCurrentAction = DYING;
		--mDyingTime;
		if (mDyingTime == 0)
		{
			m_bDying = false;
		}
		AnimationProcess();
		return;
	}
	if (m_bHit == true)
	{
		mCurrentAction = HIT;
		++mCountHitTime;
		if (mCountHitTime >= HIT_TIME)
		{
			m_bHit = false;
			mStatus.isInvulnerable = false;
			mCountHitTime = 0;
		}
		AnimationProcess();

		return;
	}

	static int count_run = 0;
	static bool right = true;
	static int countAttack2 = 9;
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
		mCurrentAction = IDLE;
		if (CollisionManager::getInstance()->checkEnemyNearPlayer(this) <= 400)
		{
			/*if (mCurrentAction != ATTACK1)
			{
				mSavePosition = *mPosition;
			}*/
			if (mCountStamina == mStatus.STA * 5)
			{
				mCurrentAction = ATTACK2;
				mCountStamina = 0;
				countAttack2 = 9;
			}
			else if (mCountStamina > mStatus.STA * 0)
			{
				mCurrentAction = ATTACK1;
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

	/*if (sideStuck() == 1 && mVelocity->getX() < 0)
	{
		mVelocity->setX(0);
		right = true;
	}
	if (sideStuck() == 2 && mVelocity->getX() > 0)
	{
		mVelocity->setX(0);
		right = false
	}*/
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
		static int wakeTime = 12;
		if (wakeTime > 0)
		{
			mCountStamina = 0;
			mCurrentAction = WAKE_UP;
			--wakeTime;
		}
	}
	//std::cout << mVelocity->getX() << '\n';
	AnimationProcess();
	*mVelocity += *mAcceleration;
	*mPosition += *mVelocity;

	animation->setPosition(*mPosition);
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
	animation->update();
}

bool DroidZapper::onGround()
{
	return CollisionManager::getInstance()->checkEnemyOnGround(this);
}

