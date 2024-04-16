#include "VideoPlayer.h"

#include "TextureManager.h"
#include "GameManager.h"

using namespace std;
VideoPlayer* VideoPlayer::s_pInstance = nullptr;

void VideoPlayer::updateFrame()
{
	++mIndexFrame;
	if (mIndexFrame == mNumFrames)
	{
		mIndexFrame = 0;
	}
}

void VideoPlayer::renderFrame()
{
	string filePath = to_string(mIndexFrame);
	while (filePath.size() < 3)
	{
		filePath = "0" + filePath;
	}
	filePath = mFilePath + filePath + ".png";
	std::cout << filePath << '\n';
	TextureManager::getInstance()->load(filePath, mFilePath, GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->drawSinglePic(mFilePath, 0, 0, 1280, 768, GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->clearFromTexture(mFilePath);
}

VideoPlayer::VideoPlayer()
{
}
