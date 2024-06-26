#ifndef TextureLoader_H_
#define TextureLoader_H_

#include <string>

class TextureLoader
{
public:
	TextureLoader(const std::string& textureID, int x, int y, int w, int h,
		int numFrames, int callback = 0);
	TextureLoader(const std::string& textureID, int x, int y, int w, int h,
		int numFrames, int from, int to);
	int getX() const { return mXPos; }
	int getY() const { return mYPos; }
	int getWidth() const { return mWidth; }
	int getHeight() const { return mHeight; }
	int getNumFrames() const { return mNumFrames; }
	int getFrom() const { return mFrom; }
	int getTo() const { return mTo; }
	std::string getTextureID() const { return mTextureID; }
	int getCallbackID() const { return mCallbackID; }

private:
	int mXPos;
	int mYPos;
	int mWidth;
	int mHeight;
	int mNumFrames;
	std::string mTextureID;
	int mCallbackID;
	int mFrom;
	int mTo;
};

#endif TextureLoader_H_

