#ifndef ARCHER_H_
#define ARCHER_H_
#include "EnemyObject.h"
class Archer :
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
		//if (mCurrentAction == ATTACK1 && (animation->getIndexFrame() == 3 || animation->getIndexFrame() == 6))
		//{
		//	return true;
		//}
		return false;
	}
	virtual Animation* getAnimation()
	{
		return animation;
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
	virtual void setPosition(const GameVector& obj)
	{
		*mPosition = obj;
	}
	virtual void setStun()
	{
		mStatus.isStunned = true;
		mCountTimeStun = STUN_TIME;
	}

	virtual ~Archer();



private:
	Archer();
	bool onGround();
	void AnimationProcess();
	void completeUpdateMethod();

	friend class ArcherGenerator;
};

class ArcherGenerator :
	public BaseGenerator
{
	BaseObject* generateObject() const
	{
		return new Archer();
	}
};


#endif //ARCHER_H_