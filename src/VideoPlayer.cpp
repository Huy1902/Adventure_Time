#include "VideoPlayer.h"

#include "TextureManager.h"
#include "GameManager.h"

#include "SoundManager.h"

using namespace std;
VideoPlayer* VideoPlayer::s_pInstance = nullptr;

void VideoPlayer::setFilePath(const std::string& s, int numFrames, const string & music)
{
	mFilePath = s;
	mNumFrames = numFrames;
	mSize = 0;
	while (numFrames > 0)
	{
		numFrames /= 10;
		++mSize;
	}
	SoundManager::getInstance()->playMusic(music, -1);
}

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
	while (filePath.size() < mSize)
	{
		filePath = "0" + filePath;
	}
	filePath = mFilePath + filePath + ".png";
	TextureManager::getInstance()->load(filePath, mFilePath, GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->drawSinglePic(mFilePath, 0, 0, 1280, 768, GameManager::getInstance()->getRenderer());
	TextureManager::getInstance()->clearFromTexture(mFilePath);
}

VideoPlayer::VideoPlayer()
{
}
