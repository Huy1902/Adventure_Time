#ifndef BARRERKNIGHT_H_
#define BARRERKNIGHT_H_
#include "EnemyObject.h"

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
		if ((mCurrentAction == ATTACK1 && (animation->getIndexFrame() == 4)) || (mCurrentAction == ATTACK2 && animation->getIndexFrame() == 5))
		{
			return true;
		}
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
	virtual void setPosition(GameVector obj)
	{
		*mPosition = obj;
	}

	BarrerKnight();
	~BarrerKnight();



private:
	GameVector mSavePosition;
	int mAttackTine;
	int mAttack1Time;


	int mCharHeight;
	int mCharWidth;

	int mTimeRun;

	bool onGround();
	//int sideStuck();

	bool m_bHeadStuck;
	bool m_bRun;
	bool m_bOnGround;


	int mCountStamina;



	void AnimationProcess();
	void completeUpdateMethod();


};

#endif

