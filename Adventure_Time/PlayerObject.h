#ifndef PLAYEROBJECT_H_
#define PLAYEROBJECT_H_
#include "CharModel.h"

#include <SDL.h>

#include "Animation.h"
#include <vector>


class PlayerObject :
    public CharModel
{
public:
	PlayerObject();
	~PlayerObject();

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
	void setVelocity(const GameVector& obj)
	{
		*mVelocity = obj;
	}
	int getHeight()const 
	{
		return mCharHeight;
	}
	int getCharWidth() const
	{
		return mCharWidth;
	}
	virtual  bool isAttack() const
	{
		if (mCurrentAction == ATTACK1 && animation->getIndexFrame() >= 1 && animation->getIndexFrame() <= 3)
		{
			return true;
		}
		return false;
	}
	bool isRight() const
	{
		if (mFlip == SDL_FLIP_NONE)
		{
			return true;
		}
		return false;
	}
	void getHurt();
	int getDamage() const
	{
		return mStatus.ATK;
	}
	virtual Status* getStatus()
	{
		return &mStatus;
	}

	virtual bool isDying() const
	{
		if (mDyingTime == 1)
		{
			return false;
		}
		return true;
	}
	Animation* getAnimation()
	{
		return animation;
	}
	bool isBash() const
	{
		if (mCurrentAction == BASH && (animation->getIndexFrame() == 3 || animation->getIndexFrame() == 4))
		{
			return true;
		}
		return false;
	}
private:
	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);
	bool onGround();
	bool headStuck();
	int sideStuck();


	bool m_bHeadStuck;
	bool m_bJump;
	bool m_bOnGround;
	int mTimeAttack;
	int mLandingTime;


	bool m_bHurting;

	int mCountTimeHurt;
	void AnimationProcess();

	void completeUpdateMethod();

};

#endif
