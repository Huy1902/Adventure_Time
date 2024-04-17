#include "AnimModel.h"

AnimModel::AnimModel() :
	BaseModel()
{
	mAnimation = new Animation();
}

AnimModel::~AnimModel()
{
	delete mAnimation;
	mActions.clear();
	mTextures.clear();
	mSFXs.clear();
}

void AnimModel::processData()
{
}

void AnimModel::renderObject() const
{
}

void AnimModel::clearObject()
{
}
