#include "EnemyObject.h"
#include "GameManager.h"
#include "InputManager.h"

EnemyObject::EnemyObject() :
	ObjectModel()
{
}

EnemyObject::~EnemyObject()
{

}

void EnemyObject::loadTexture(std::unique_ptr<TextureLoader> Info)
{
	ObjectModel::loadTexture(std::move(Info));
}

void EnemyObject::processData()
{
	++mIndexFrames;
	if (mIndexFrames == mNumFrames)
	{
		mIndexFrames = 0;
	}
}

void EnemyObject::renderObject() const
{
	ObjectModel::renderObject();
}

void EnemyObject::clearObject()
{

}

void EnemyObject::run()
{
	Info temp = mActions["run"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
	/*animation->changeAnim("barrer_run", 7, mFlip);
	animation->setSize(59, 64);*/
}

void EnemyObject::none()
{
	//animation->changeAnim("barrer_none", 1, mFlip);
	//animation->setSize(63, 64);
	Info temp = mActions["none"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void EnemyObject::wake()
{
	//animation->changeAnim("barrer_wake", 4, mFlip);
	//animation->setSize(63, 64);
	Info temp = mActions["wake"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void EnemyObject::attack1()
{
	//animation->changeAnim("barrer_attack1", 5, mFlip);
	//animation->setSize(120, 64);
	//animation->setSpeed(2);
	Info temp = mActions["attack1"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void EnemyObject::hit()
{
	//animation->changeAnim("barrer_hit", 2, mFlip);
	//animation->setSize(120, 64);
	//animation->setSpeed(2);
	Info temp = mActions["hit"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void EnemyObject::attack2()
{
	Info temp = mActions["attack2"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void EnemyObject::dying()
{
	Info temp = mActions["dying"];
	animation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

