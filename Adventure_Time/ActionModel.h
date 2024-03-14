#ifndef ACTIONMODEL_H_
#define ACTIONMODEL_H_

#include "BaseAction.h"

class ActionModel :
	public BaseAction
{
public:
	ActionModel();
	~ActionModel();

	virtual void setCallback(void(*callback)()) { mCallback = callback; }
	virtual void processData();
	virtual void renderAction();
	virtual bool onEnter();
	virtual bool onExit();
	std::string getActionID() const { return mActionID; }

	//update postition
	virtual void setPos(const GameVector& other)
	{
		*mPosition = other;
	}
	GameVector* getPos() const
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

	int mHeight;
	int mWidth;
	GameVector* mPosition;
	int mIndexFrames;
	int mNumFrames;

	GameVector* mPosition;

	int mWidth;
	int mHeight;

};
#endif
