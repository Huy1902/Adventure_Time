#include "CharModel.h"

CharModel::CharModel() : 
	AnimModel()
{
	mVelocity = new GameVector();
	mAcceleration = new GameVector();
}

CharModel::~CharModel()
{
	delete mVelocity;
	delete mAcceleration;
}

//void CharModel::loadTexture(std::unique_ptr<TextureLoader> Info)
//{
//}

void CharModel::processData()
{
}

void CharModel::renderObject() const
{
}

void CharModel::clearObject()
{
}

void CharModel::run()
{
	Info temp = mActions["run"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::jump()
{
	Info temp = mActions["jump"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::idle()
{
	Info temp = mActions["idle"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::fall()
{
	Info temp = mActions["fall"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::attack1()
{
	Info temp = mActions["attack1"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::hurt()
{
	Info temp = mActions["hurt"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::landing()
{
	Info temp = mActions["landing"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::dash()
{
	Info temp = mActions["dash"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::dying()
{
	mVelocity->setX(0);
	Info temp = mActions["dying"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}


void CharModel::none()
{
	Info temp = mActions["none"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::wake()
{
	Info temp = mActions["wake"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::hit()
{
	Info temp = mActions["hit"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::attack2()
{
	Info temp = mActions["attack2"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::bash()
{
	Info temp = mActions["bash"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::crit()
{
	Info temp = mActions["crit"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::stun()
{
	Info temp = mActions["stun"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}
