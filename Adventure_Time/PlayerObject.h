#ifndef PLAYEROBJECT_H_
#define PLAYEROBJECT_H_
#include "ObjectModel.h"

#include <SDL.h>

class PlayerObject :
    public ObjectModel
{
public:
	PlayerObject();
	~PlayerObject();

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);
	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();

	GameVector* getVelocity() 
	{
		return mVelocity;
	}
	GameVector* getPosition()
	{
		return mPosition;
	}
	void setPosition(const GameVector& obj)
	{
		*mPosition = obj;
	}
	void setPositionX(const double& val)
	{
		mPosition->setX(val);
	}
	void setPositionY(const double& val)
	{
		mPosition->setY(val);
	}
	void setVelocity(const GameVector& obj)
	{
		*mVelocity = obj;
	}
	void setVelocityX(const double& val)
	{
		mVelocity->setX(val);
	}
	void setVelocityY(const double& val)
	{
		mVelocity->setY(val);
	}
	int getHeight()const 
	{
		return mCharHeight;
	}
	int getCharWidth() const
	{
		return mCharWidth;
	}
private:

	GameVector* mVelocity;
	GameVector* mAcceleration;

	bool m_bRight;


	std::map<std::string, ActionModel*> mActionMap;
	//ActionModel* mCurrentAction;

	int mCharHeight;
	int mCharWidth;

	bool onGround();
	bool headStuck();
	int sideStuck();

	bool m_bHeadStuck;
	bool m_bJump;
	bool m_bRun;
	bool m_bOnGround;
	SDL_RendererFlip mFlip;

	void AnimationProcess();

	enum Action
	{
		RUN = 0,
		JUMP = 1,
		IDLE = 2,
		FALL = 3
	};

	Action mCurrentAction;
	Action mBackAction;
};

#endif
