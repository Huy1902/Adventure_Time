#ifndef BARRERKNIGHT_H_
#define BARRERKNIGHT_H_
#include "EnemyObject.h"

#include "BaseGenerator.h"
#include <SDL.h>



class BarrerKnight :
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
		if ((mCurrentAction == ATTACK1 && (mAnimation->getIndexFrame() == 4)) || (mCurrentAction == ATTACK2 && mAnimation->getIndexFrame() == 5))
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

	virtual ~BarrerKnight();



private:
	BarrerKnight();
	bool onGround();
	void AnimationProcess();
	void completeUpdateMethod();

	friend class BarrerKnightGenerator;
};

class BarrerKnightGenerator :
	public BaseGenerator
{
	BaseObject* generateObject() const
	{
		return new BarrerKnight();
	}
};

#endif
