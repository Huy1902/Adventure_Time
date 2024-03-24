#include "StatusManager.h"

#include "TextureManager.h"
#include "GameManager.h"
StatusManager* StatusManager::s_pInstance = nullptr;

void StatusManager::updatePlayerStatus()
{
	mCurrentPlayer = *mPlayer->getStatus();
	mSrcPoint.w = mDestPoint.w = (mCurrentPlayer.HP * 1.0 / mMaxPlayer.HP) * mLenPoint;
}

void StatusManager::renderPlayerStatus()
{
	SDL_RenderCopy(GameManager::getInstance()->getRenderer(), TextureManager::getInstance()->getTexture("health_point"), &mSrcPoint, &mDestPoint);
	SDL_RenderCopy(GameManager::getInstance()->getRenderer(), TextureManager::getInstance()->getTexture("health_bar"), & mSrcHealth, &mDestHealth);
}

void StatusManager::setPlayer(PlayerObject* obj)
{
	mPlayer = obj;
	mMaxPlayer = *obj->getStatus();
}

StatusManager::StatusManager()
{
	TextureManager::getInstance()->load("assets/status/health_bar.png", "health_bar", GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->load("assets/status/health_point.png", "health_point", GameManager::getInstance()->getRenderer());
	mSrcPoint = { 0, 0, 140, 10 };
	mDestPoint = { 47, 27, 140, 10 };
	mSrcHealth = { 0, 0, 190, 57 };
	mDestHealth = { 0, 0, 190, 57 };

	mLenPoint = mSrcPoint.w;
}

StatusManager::~StatusManager()
{
}

