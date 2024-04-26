#include "TextureLoader.h"


TextureLoader::TextureLoader(const std::string& textureID, int x, int y, int w, int h, int numFrames, int callback):
	mTextureID(textureID),
	mXPos(x),
	mYPos(y),
	mWidth(w),
	mHeight(h),
	mNumFrames(numFrames),
	mCallbackID(callback)
{
}

TextureLoader::TextureLoader(const std::string& textureID, int x, int y, int w, int h, int numFrames, int from, int to) :
	mTextureID(textureID),
	mXPos(x),
	mYPos(y),
	mWidth(w),
	mHeight(h),
	mNumFrames(numFrames),
	mFrom(from),
	mTo(to)
{
}
