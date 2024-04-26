#include "Darkra.h"
#include "TextureManager.h"
#include "GameManager.h"
#include "ObjectParser.h"

Darkra::Darkra() :
	SpellObject()
{
	//on Map only exist one instance of magic at one time
	ObjectParser::getInstance()->parserCharacter("darkra.xml", mActions, mTextures, mSFXs);
	for (const auto& ite : mTextures)
	{
		TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	}
	mCountTimeExist = mActions["cast"].numFrames * mActions["cast"].speed;

	mVelocity->setX(6);
	mVelocity->setY(0);
	mCastDistance = 100;
	mCurrentAction = CAST;
	ATK = 30;
}

Darkra::~Darkra()
{
}

void Darkra::processData()
{
	--mCountTimeExist;
	if (m_bHaveCollision == true)
	{
		mCurrentAction = COLLISION;
		mVelocity->setX(0);
	}
	SpellObject::processData();
}

void Darkra::renderObject() const
{
	SpellObject::renderObject();
}

void Darkra::clearObject()
{
}