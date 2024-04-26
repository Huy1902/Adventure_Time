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
		return mAnimation;
	}
	virtual int getDamage() const
	{
		return mStatus.ATK;
	}
	virtual bool isAlive()
	{
		if (mFlyingTime == 0 || mStatus.isAlive == false)
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
	virtual void setPosition(const GameVector& obj)
	{
		*mPosition = obj;
	}
	void setDirection(bool isRight);
	void setDying()
	{
		mStatus.isAlive = false;
	}
	virtual ~Arrow();



private:
	Arrow();
	bool onGround();
	void AnimationProcess();
	void completeUpdateMethod();

	friend class ArrowGenerator;
	friend class ArrowManager;
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