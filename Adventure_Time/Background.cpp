#include "Background.h"

#include <random>

#include "TextureManager.h"
#include "GameManager.h"
#include "SoundManager.h"

const int TIME_TO_MOVE = 10;
Background::Background()
{
	srand(time(NULL));

	int i = rand() % 2;
	if (i == 0)
	{
		TextureManager::getInstance()->load("assets/background1.png", "background1", GameManager::getInstance()->getRenderer());
		SoundManager::getInstance()->playMusic("home_theme", -1);
	}
	else
	{
		TextureManager::getInstance()->load("assets/background3.png", "background1", GameManager::getInstance()->getRenderer());
		SoundManager::getInstance()->playMusic("night_theme", -1);
	}

	mWindowsWidth = GameManager::getInstance()->getWidthWindows() / 2;
	mWindowsHeight = GameManager::getInstance()->getHeightWindows();
	mCountTime = 0;
	mScrollSpeed = 1;

	reset();
}

Background::~Background()
{
	TextureManager::getInstance()->clearFromTexture("background1");
}

void Background::drawBackground()
{

	SDL_RenderCopy(GameManager::getInstance()->getRenderer(), TextureManager::getInstance()->getTexture("background1"), &mSrc1, &mDest1);
	SDL_RenderCopy(GameManager::getInstance()->getRenderer(), TextureManager::getInstance()->getTexture("background1"), &mSrc2, &mDest2);
}

void Background::updateBackground()
{
	/*if (mCountTime == TIME_TO_MOVE)
	{*/
		mCountTime = 0;
		mSrc1.x += mScrollSpeed;
		mSrc1.w -= mScrollSpeed;
		mDest1.w -= mScrollSpeed;

		mSrc2.w += mScrollSpeed;
		mDest2.w += mScrollSpeed;
		mDest2.x -= mScrollSpeed;

		if (mSrc1.x == mWindowsWidth * 2)
		{
			reset();
		}
	//}
}

void Background::reset()
{
	mSrc1 = { 0, 0, mWindowsWidth * 2, mWindowsHeight };
	mSrc2 = { 0, 0, 0, mWindowsHeight};
	mDest1 = { 0, 0, mWindowsWidth * 2, mWindowsHeight };
	mDest2 = { mWindowsWidth * 2, 0, 0, mWindowsHeight };
}
