#ifndef ARROW_H_
#define ARROW_H_
#include "EnemyObject.h"
class Arrow :
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
		return true;
	}
	virtual Animation* getAnimation()
	{
		return animation;
	}
	virtual int getDamage() const
	{
		return mStatus.ATK;
	}
	virtual bool isAlive()
	{
		if (mFlyingTime == 0)
		{
			return false;
		}
		return true;
	}

	virtual int getHeight()const
	{
		return mCharHeight;
	}
	virtual int getCharWidth() const
	{
		return mCharWidth;
	}
	virtual void setPosition(GameVector obj)
	{
		*mPosition = obj;
	}
	void setDirection(const GameVector& direct)
	{
		*mVelocity = direct;
	}
	virtual ~Arrow();
	Arrow();



private:
	bool onGround();
	void AnimationProcess();
	void completeUpdateMethod();

	friend class ArrowGenerator;

	void fly();

	int mFlyingTime;
};

class ArrowGenerator :
	public BaseGenerator
{
	BaseObject* generateObject() const
	{
		return new Arrow();
	}
};

#endif // ARROW_H_