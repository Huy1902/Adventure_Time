#include "AchieveManager.h"
#include "ObjectParser.h"
#include "TextureManager.h"
#include "GameManager.h"

AchieveManager* AchieveManager::s_pInstance = nullptr;
void AchieveManager::takeAchieve(Achieve_type archive)
{
	if (mCountTimeAnimation != 0)
	{
		endAchieve();
	}
	mCurrentAchieve = archive;
	switch (archive)
	{
	case BONFIRE_LIT:
		startAchieve("bonfire");
		break;
	case BOSS_DESTROYED:
		startAchieve("boss");
		break;
	case BONFIRE_REVIVAL:
		startAchieve("revival");
		break;
	case MAIN_DEATH:
		startAchieve("death");
		break;
	case NEW_AREA:
		startAchieve("new_area");
		break;
	}
}

void AchieveManager::renderAchieve()
{
	if (mCurrentAchieve != NONE_ARCHIEVE)
	{
		mAnimation->draw();
	}
}

void AchieveManager::updateAchieve()
{
	if (mCountTimeAnimation == 0)
	{
		endAchieve();
		mCurrentAchieve = NONE_ARCHIEVE;
	}
	else
	{
		--mCountTimeAnimation;
		mAnimation->update();
	}
}

void AchieveManager::startAchieve(const std::string& name)
{
	switch (mCurrentAchieve)
	{
	case BOSS_DESTROYED:
		loadTexture(0);
		break;
	case BONFIRE_LIT:
		loadTexture(1);
		break;
	case BONFIRE_REVIVAL:
		loadTexture(2);
		break;
	case MAIN_DEATH:
		loadTexture(3);
		break;
	case NEW_AREA:
		loadTexture(4);
		break;
	}
	mCountTimeAnimation = mAchieve[name].numFrames * mAchieve[name].speed - 1;
	mAnimation->changeAnim(mAchieve[name].textureID, mAchieve[name].numFrames, SDL_FLIP_NONE, 1280, 768, mAchieve[name].speed);
	mAnimation->resetIndexFrame();
}

void AchieveManager::loadTexture(int i)
{
	TextureManager::getInstance()->load(mTexture[i].filePath, mTexture[i].textureID, GameManager::getInstance()->getRenderer());
}

void AchieveManager::clearTexture(int i)
{
	TextureManager::getInstance()->clearFromTexture(mTexture[i].textureID);
}

void AchieveManager::endAchieve()
{
	switch (mCurrentAchieve)
	{
	case BOSS_DESTROYED:
		clearTexture(0);
		break;
	case BONFIRE_LIT:
		clearTexture(1);
		break;
	case BONFIRE_REVIVAL:
		clearTexture(2);
		break;
	case MAIN_DEATH:
		clearTexture(3);
		break;
	case NEW_AREA:
		clearTexture(4);
		break;
	}
}

AchieveManager::AchieveManager()
{
	mCountTimeAnimation = 0;
	mAnimation = new Animation();
	mAnimation->setPosition(GameVector(0, 0));
	ObjectParser::getInstance()->parserTexture("Achieve.xml", mTexture);
	ObjectParser::getInstance()->parserAction("Achieve.xml", mAchieve);
	mCurrentAchieve = NONE_ARCHIEVE;
}

AchieveManager::~AchieveManager()
{
	mTexture.clear();
	mAchieve.clear();
	delete mAnimation;
}


