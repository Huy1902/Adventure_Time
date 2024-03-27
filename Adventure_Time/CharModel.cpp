#include "CharModel.h"

CharModel::CharModel()
{
}

CharModel::~CharModel()
{
}

void CharModel::loadTexture(std::unique_ptr<TextureLoader> Info)
{
}

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
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::jump()
{
	Info temp = mActions["jump"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::idle()
{
	Info temp = mActions["idle"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::fall()
{
	Info temp = mActions["fall"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::attack1()
{
	Info temp = mActions["attack1"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::hurt()
{
	Info temp = mActions["hurt"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::landing()
{
	Info temp = mActions["landing"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::dash()
{
	Info temp = mActions["dash"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::dying()
{
	Info temp = mActions["dying"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}


void CharModel::none()
{
	Info temp = mActions["none"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::wake()
{
	Info temp = mActions["wake"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::hit()
{
	Info temp = mActions["hit"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::attack2()
{
	Info temp = mActions["attack2"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::bash()
{
	Info temp = mActions["bash"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::crit()
{
	Info temp = mActions["crit"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void CharModel::stun()
{
	Info temp = mActions["stun"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}
