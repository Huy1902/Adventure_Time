#include "BarrerKnight.h"

#include "TextureManager.h"
#include "GameManager.h"
#include "CollisionManager.h"

const int MOVE_SPEED = 2;
const int GRAVITY = 4;
const int UP_FORCE = -20;


BarrerKnight::BarrerKnight() :
	EnemyObject()
{
	TextureManager::getInstance()->load("assets/barrel_knight/run.png", "barrer_run", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/barrel_knight/wake.png", "barrer_wake", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/barrel_knight/none.png", "barrer_none", GameManager::getInstance()->getRenderer());

	animation = new Animation();


	mPosition = new GameVector(1400, 600);
	mVelocity = new GameVector(0, 0);
	mAcceleration = new GameVector(0, 0);
	mMapPosition = new GameVector(0, 0);

	mCurrentAction = IDLE;
	animation->setPosition(*mPosition);

	mTimeRun = 100;
}

BarrerKnight::~BarrerKnight()
{
	TextureManager::getInstance()->clearFromTexture("barrer_run");
	TextureManager::getInstance()->clearFromTexture("barrer_wake");
	TextureManager::getInstance()->clearFromTexture("barrer_none");
}

void BarrerKnight::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	ObjectModel::loadTexture(std::move(Info));
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
		wakeUp();
		break;
	case BarrerKnight::FALL:
		none();
		break;
	case BarrerKnight::IDLE:
		none();
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
	animation->changeAnim("barrer_run", 7, mFlip);
	animation->setSize(59, 64);
}

void BarrerKnight::none()
{
	animation->changeAnim("barrer_none", 1, mFlip);
	animation->setSize(63, 64);
}

void BarrerKnight::wakeUp()
{
	animation->changeAnim("barrer_wake", 4, mFlip);
	animation->setSize(63, 64);
}

