#ifndef GAMEMODEL_H_
#define GAMEMODEL_H_

#include "GameObject.h"

class GameModel :
    public GameObject
{
public:
	GameModel();
	~GameModel();

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);
	virtual void processData();
	virtual void renderObject() const;
	virtual void cleanObject();

protected:
	std::string mTextureID;

	int mIndexFrames;
	int mXPos;
	int mYPos;
	int mWidth;
	int mHeight;
	int mNumFrames;
	double mScope;
};

#endif

