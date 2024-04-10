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

	animation = new Animation();


	mPosition = new GameVector();
	mVelocity = new GameVector(0, 0);
	mAcceleration = new GameVector(0, 0);
	mMapPosition = new GameVector(0, 0);
	mStatus.ATK = 20;

	animation->setPosition(*mPosition);
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
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

Arrow::~Arrow()
{
}

void Arrow::renderObject() const
{
	animation->setPosition(*mPosition - *mMapPosition);
	animation->draw();
}

void Arrow::clearObject()
{
	//for (const auto& ite : mTextures)
	//{
	//	TextureManager::getInstance()->clearFromTexture(ite.textureID);
	//}
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
	animation->update();
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

	animation->setPosition(*mPosition);
}

void Arrow::fly()
{
	Info temp = mActions["flying"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}