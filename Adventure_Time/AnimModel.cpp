#include "AnimModel.h"

#include "TextureManager.h"
#include "SoundManager.h"
AnimModel::AnimModel() :
	BaseModel()
{
	mAnimation = new Animation();
}

AnimModel::~AnimModel()
{
	delete mAnimation;
	for (const auto& ite : mTextures)
	{
		TextureManager::getInstance()->clearFromTexture(ite.textureID);
	}
	mTextures.clear();
	mActions.clear();
	for (const auto& ite : mSFXs)
	{
		SoundManager::getInstance()->clearSFX(ite.second.sfxID);
	}
	mSFXs.clear();
}

void AnimModel::processData()
{
	mAnimation->update();
}

void AnimModel::renderObject() const
{
	mAnimation->draw();
}

void AnimModel::clearObject()
{
}
