#ifndef VAGABOND_H_
#define VAGABOND_H_
#include "EnemyObject.h"
class Vagabond :
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
	virtual bool isAttack() const;
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
	virtual ~Vagabond();
private:
	Vagabond();
	bool onGround();
	void AnimationProcess();
	void completeUpdateMethod();

	friend class VagabondGenerator;
};

class VagabondGenerator :
	public BaseGenerator
{
	BaseObject* generateObject() const
	{
		return new Vagabond();
	}
};
#endif
