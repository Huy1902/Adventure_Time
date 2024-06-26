#include "SpellObject.h"

SpellObject::SpellObject() :
	AnimModel()
{
	mMapPosition = new GameVector();
	mVelocity = new GameVector();
	mCastDistance = 0;
	ATK = 10;
}

SpellObject::~SpellObject()
{
	delete mMapPosition;
	delete mVelocity;
}

void SpellObject::processData()
{
	--mCountTimeExist;
	completeUpdateMethod();
	AnimModel::processData();
}

void SpellObject::renderObject() const
{
	mAnimation->setPosition(*mPosition - *mMapPosition);
	AnimModel::renderObject();
}

void SpellObject::clearObject()
{
}

void SpellObject::completeUpdateMethod()
{
	AnimationProcess();
	*mPosition += *mVelocity;
}

void SpellObject::AnimationProcess()
{
	switch (mCurrentAction)
	{
	case SpellObject::CAST:
		cast();
		break;
	case SpellObject::COLLISION:
		collision();
		break;
	default:
		break;
	}
}

void SpellObject::cast()
{
	Info temp = mActions["cast"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}

void SpellObject::collision()
{
	Info temp = mActions["collision"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}
