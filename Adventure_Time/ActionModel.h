#ifndef ACTIONMODEL_H_
#define ACTIONMODEL_H_

#include "BaseObject.h"
#include "GameVector.h"

class ActionModel :
    public BaseObject
{
public:
	ActionModel();
	~ActionModel();

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);

	//update postition
	virtual void setPos(double x_, double y_)
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
	virtual bool isOnAir() const
	{
		return m_bOnAir;
	}
	virtual void setOnAir(bool b_)
	{
		m_bOnAir = b_;
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
	double mScope;
	bool m_bRight;
	bool m_bOnAir;
};

#endif
