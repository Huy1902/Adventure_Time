#include "TextureLoader.h"


TextureLoader::TextureLoader(const std::string& textureID, int x, int y, int w, int h, int numFrames, float scope):
	mTextureID(textureID),
	mXPos(x),
	mYPos(y),
	mWidth(w),
	mHeight(h),
	mNumFrames(numFrames),
	mScope(scope)
{
}
