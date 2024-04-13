#include "AchieveManager.h"
#include "ObjectParser.h"
#include "TextureManager.h"
#include "GameManager.h"

AchieveManager* AchieveManager::s_pInstance = nullptr;
void AchieveManager::takeAchieve(Achieve_type archive)
{
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
	mCountTimeAnimation = mAchieve[name].numFrames * mAchieve[name].speed - 1;
	mAnimation->changeAnim(mAchieve[name].textureID, mAchieve[name].numFrames, SDL_FLIP_NONE, 1280, 768, mAchieve[name].speed);
}

AchieveManager::AchieveManager()
{
	mCountTimeAnimation = 0;
	mAnimation = new Animation();
	mAnimation->setPosition(GameVector(0, 0));
	ObjectParser::getInstance()->parserTexture("Achieve.xml", mTexture);
	for (auto& ite : mTexture)
	{
		TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	}
	ObjectParser::getInstance()->parserAction("Achieve.xml", mAchieve);
	mCurrentAchieve = NONE_ARCHIEVE;
}

AchieveManager::~AchieveManager()
{
	for (const auto& ite : mTexture)
	{
		TextureManager::getInstance()->clearFromTexture(ite.textureID);
	}
	mTexture.clear();
	mAchieve.clear();
	delete mAnimation;
}


