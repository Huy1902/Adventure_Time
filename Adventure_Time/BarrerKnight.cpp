#include "BarrerKnight.h"

#include "TextureManager.h"
#include "GameManager.h"
#include "CollisionManager.h"

#include "ObjectParser.h"

const int MOVE_SPEED = 2;
const int GRAVITY = 4;
const int UP_FORCE = -20;
const int ATTACK1_TIME = 100;
const int HIT_TIME = 8;

void BarrerKnight::getHurt()
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

BarrerKnight::BarrerKnight() :
	EnemyObject()
{
	/*TextureManager::getInstance()->load("assets/barrel_knight/run.png", "barrer_run", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/barrel_knight/wake.png", "barrer_wake", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/barrel_knight/none.png", "barrer_none", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/barrel_knight/attack1.png", "barrer_attack1", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/barrel_knight/hit.png", "barrer_hit", GameManager::getInstance()->getRenderer());*/

	ObjectParser::getInstance()->parserAction("BarerKnight.xml", actions, textureVector);
	for (const auto& ite : textureVector)
	{
		TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	}

	animation = new Animation();


	mPosition = new GameVector(1400, 600);
	mVelocity = new GameVector(0, 0);
	mAcceleration = new GameVector(0, 0);
	mMapPosition = new GameVector(0, 0);

	mCurrentAction = IDLE;
	animation->setPosition(*mPosition);

	mTimeRun = 100;

	mStatus.HP = 200;

	mCountHitTime = 0;

	mCountStamina = 0;
}
BarrerKnight::~BarrerKnight()
{
	for (const auto& ite : textureVector)
	{
		TextureManager::getInstance()->clearFromTexture(ite.textureID);
	}
}

//void BarrerKnight::loadTexture(std::unique_ptr<TextureLoader> Info)
//{
//	ObjectModel::loadTexture(std::move(Info));
//}
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
		if (countAttack2 > 0)
		{
			mCurrentAction = ATTACK2;
			--countAttack2;
			if (animation->getIndexFrame() == 4)
			{
				if (mFlip == SDL_FLIP_HORIZONTAL)
				{
					mVelocity->setX(-200);
				}
				else
				{
					mVelocity->setX(200);
				}
			}
		}
		else
		{
			mCurrentAction = RUN;
		}
		if (CollisionManager::getInstance()->checkEnemyNearPlayer(this) == true)
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

			if (mCurrentAction != ATTACK2)
			{
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

			//++mAttack1Time;
			//if (mAttack1Time == ATTACK1_TIME)
			//{
			//	mAttack1Time = 0;
			//}
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
	if (m_bSleep == true)
	{
		mCountStamina = 0;
		mCurrentAction = IDLE;
		mVelocity->setX(0);
		if (CollisionManager::getInstance()->checkEnemyNearPlayer(this) == true)
		{
			m_bSleep = false;
			static int countWake = 100;
			--countWake;
			if (countWake == 0)
			{
			}
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
	AnimationProcess();
	//std::cout << mVelocity->getX() << '\n';
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
		wakeUp();
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
	default:
		break;
	}
	animation->update();
}

bool BarrerKnight::onGround()
{
	return CollisionManager::getInstance()->checkEnemyOnGround(this);
}

//int BarrerKnight::sideStuck()
//{
//	if (CollisionManager::getInstance()->checkPlayerSideLeft() == true)
//	{
//		return 1;
//	}
//	else
//		if (CollisionManager::getInstance()->checkPlayerSideRight() == true)
//		{
//			return 2;
//		}
//	return 0;
//}


void BarrerKnight::run()
{
	Info temp = actions["run"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
	/*animation->changeAnim("barrer_run", 7, mFlip);
	animation->setSize(59, 64);*/
}

void BarrerKnight::none()
{
	//animation->changeAnim("barrer_none", 1, mFlip);
	//animation->setSize(63, 64);
	Info temp = actions["none"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void BarrerKnight::wakeUp()
{
	//animation->changeAnim("barrer_wake", 4, mFlip);
	//animation->setSize(63, 64);
	Info temp = actions["wake"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void BarrerKnight::attack1()
{
	//animation->changeAnim("barrer_attack1", 5, mFlip);
	//animation->setSize(120, 64);
	//animation->setSpeed(2);
	Info temp = actions["attack1"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void BarrerKnight::hit()
{
	//animation->changeAnim("barrer_hit", 2, mFlip);
	//animation->setSize(120, 64);
	//animation->setSpeed(2);
	Info temp = actions["hit"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void BarrerKnight::attack2()
{
	Info temp = actions["attack2"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

