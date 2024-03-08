#ifndef ACTIONMODEL_H_
#define ACTIONMODEL_H_

#include "GameObject.h"
#include "GameVector.h"

class ActionModel :
    public GameObject
{
public:
	ActionModel(const std::string textureID, int w, int h, int numFrames, float scope);
	~ActionModel();

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);

	//update postition
	virtual void setPos(int x_, int y_)
	{
		mPosition = std::make_pair(x_, y_);
	}

	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();

protected:
	std::string mTextureID;

	GameSize mSize;

	int mIndexFrames;
	int mNumFrames;
	float mScope;
};

#endif
