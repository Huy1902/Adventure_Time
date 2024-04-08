#include "Arrow.h"

#include "TextureManager.h"
#include "GameManager.h"
#include "CollisionManager.h"

#include "ObjectParser.h"

const int MOVE_SPEED = 2;
const int GRAVITY = 4;
const int UP_FORCE = -20;
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

	animation->setPosition(*mPosition);

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
	//mAcceleration->setY(GRAVITY);
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