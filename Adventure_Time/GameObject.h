#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

//C++lin
#include <iostream>

//project file
#include "TextureLoader.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	void loadTexture(const TextureLoader* Info);
	void processData();
	void renderObject() const;
	void cleanObject();

private:
	std::string mTextureID;

	int mIndexFrames;
	int mXPos;
	int mYPos;
	int mWidth;
	int mHeight;
	int mNumFrames;
	double mScope;
};

#endif GAMEOBJECT_H_

