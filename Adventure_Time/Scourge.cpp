#include "Scourge.h"

#include "TextureManager.h"
#include "GameManager.h"
#include "ObjectParser.h"

Scourge::Scourge() :
	SpellObject()
{
	//on Map only exist one instance of magic at one time
	ObjectParser::getInstance()->parserCharacter("scourge.xml", mActions, mTextures, mSFXs);
	for (const auto& ite : mTextures)
	{
		TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	}
	mCountTimeExist = mActions["cast"].numFrames * mActions["cast"].speed;

	mVelocity->setX(0);
	mVelocity->setY(0);
	mCastDistance = 100;
}

Scourge::~Scourge()
{
}

void Scourge::processData()
{
	mCurrentAction = CAST;
	SpellObject::processData();
}

void Scourge::renderObject() const
{
	SpellObject::renderObject();
}

void Scourge::clearObject()
{
}
