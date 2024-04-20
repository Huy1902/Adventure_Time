#include "SpellObject.h"

SpellObject::SpellObject() :
	AnimModel()
{
	mMapPosition = new GameVector();
	mVelocity = new GameVector();
	mCastDistance = 0;
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
	default:
		break;
	}
	mAnimation->update();
}

void SpellObject::cast()
{
	Info temp = mActions["cast"];
	mAnimation->changeAnim(temp.textureID, temp.numFrames, mFlip, temp.w, temp.h, temp.speed);
}
