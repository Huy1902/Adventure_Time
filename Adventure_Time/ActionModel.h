#ifndef ACTIONMODEL_H_
#define ACTIONMODEL_H_

#include "GameObject.h"
#include "GameVector.h"

class ActionModel :
    public GameObject
{
public:
	ActionModel();
	~ActionModel();

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);

	//update postition
	virtual void setPos(float x_, float y_)
	{
		mPosition = std::make_pair(x_, y_);
	}
	GameVector getPos() const
	{
		return mPosition;
	}
	virtual void setRightMove(bool b_)
	{
		m_bRight = b_;
	}
	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();

protected:
	std::string mTextureID;

	GameSize mSize;
	GameVector mPosition;
	int mIndexFrames;
	int mNumFrames;
	float mScope;
	bool m_bRight;
};

#endif
