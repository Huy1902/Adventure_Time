#include "Arrow.h"

#include "TextureManager.h"
#include "GameManager.h"
#include "CollisionManager.h"

#include "ObjectParser.h"

const int MOVE_SPEED = 40;
const int GRAVITY = 1;
const int UP_FORCE = -10;
const int TIME_RUN = 100;

Arrow::Arrow() :
	EnemyObject()
{

	ObjectParser::getInstance()->parserAction("arrow.xml", mActions);

	mStatus.ATK = 20;

	mAnimation->setPosition(*mPosition);
}
void Arrow::setDirection(bool isRight)
{
	mVelocity->setY(UP_FORCE);
	mAcceleration->setY(GRAVITY);
	if (isRight)
	{
		mFlip = SDL_FLIP_NONE;
		mVelocity->setX(MOVE_SPEED);
	}
	else
	{
		mFlip = SDL_FLIP_HORIZONTAL;
		mVelocity->setX(-MOVE_SPEED);
	}

	mFlyingTime = mActions["flying"].numFrames * mActions["flying"].speed - 1;
	Info temp = mActions["flying"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

Arrow::~Arrow()
{
}

void Arrow::renderObject() const
{
	mAnimation->draw();
}

void Arrow::clearObject()
{
}

void Arrow::processData()
{
	if (mFlyingTime > 0)
	{
		--mFlyingTime;
		completeUpdateMethod();
	}
}

void Arrow::AnimationProcess()
{
	fly();
	mAnimation->update();
}

bool Arrow::onGround()
{
	return CollisionManager::getInstance()->checkEnemyOnGround(this);
}

void Arrow::completeUpdateMethod()
{
	AnimationProcess();

	*mVelocity += *mAcceleration;
	*mPosition += *mVelocity;
	mAnimation->setPosition(*mPosition - *mMapPosition);
}

void Arrow::fly()
{
	Info temp = mActions["flying"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}