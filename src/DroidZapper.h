#ifndef DROIDZAPPER_H_
#define DROIDZAPPER_H_

#include "EnemyObject.h"

#include <SDL.h>
#include "BaseGenerator.h"

class DroidZapper :
    public EnemyObject
{
public:
	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();
	virtual void setMapPosition(const GameVector& pos)
	{
		*mMapPosition = pos;
	}


	virtual bool isRight() const
	{
		if (mFlip == SDL_FLIP_NONE)
		{
			return true;
		}
		return false;
	}
	virtual bool isAttack() const
	{
		if (mCurrentAction == ATTACK1 && (mAnimation->getIndexFrame() == 3 || mAnimation->getIndexFrame() == 6)) 
		{
			return true;
		}
		return false;
	}
	virtual Animation* getAnimation()
	{
		return mAnimation;
	}
	virtual int getDamage() const
	{
		return mStatus.ATK;
	}
	virtual void getHurt();
	virtual bool isAlive()
	{
		return mStatus.isAlive;
	}

	virtual int getHeight()const
	{
		return mCharHeight;
	}
	virtual int getCharWidth() const
	{
		return mCharWidth;
	}
	virtual bool isDying() const
	{
		if (mDyingTime == 1)
		{
			return false;
		}
		return true;
	}
	virtual void setPosition(GameVector obj)
	{
		*mPosition = obj;
	}
	virtual void setStun()
	{
		mStatus.isStunned = true;
		mCountTimeStun = STUN_TIME;
	}

	virtual ~DroidZapper();



private:
	DroidZapper();
	bool onGround();
	void AnimationProcess();
	void completeUpdateMethod();

	friend class DroidZapperGenerator;
};

class DroidZapperGenerator :
	public BaseGenerator
{
	BaseObject* generateObject() const
	{
		return new DroidZapper();
	}
};

#endif

