#ifndef TextureLoader_H_
#define TextureLoader_H_

#include <string>

class TextureLoader
{
public:
	TextureLoader(const std::string& textureID, int x, int y, int w, int h,
		int numFrames, float scope = 1.0);

	int getX() const { return mXPos; }
	int getY() const { return mYPos; }
	int getWidth() const { return mWidth; }
	int getHeight() const { return mHeight; }
	int getNumFrames() const { return mNumFrames; }
	float getScope() const { return mScope; }
	std::string getTextureID() const { return mTextureID; }

private:
	int mXPos;
	int mYPos;
	int mWidth;
	int mHeight;
	int mNumFrames;
	std::string mTextureID;
	float mScope;
};

#endif TextureLoader_H_

