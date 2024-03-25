#ifndef DROIDZAPPER_H_
#define DROIDZAPPER_H_

#include "EnemyObject.h"

#include <SDL.h>
class DroidZapper :
    public EnemyObject
{
public:

	//virtual void loadTexture(std::unique_ptr<TextureLoader> Info);
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
	virtual bool getDying()
	{
		return m_bDying;
	}

	DroidZapper();
	~DroidZapper();



private:
	GameVector mSavePosition;
	int mAttackTine;

	bool m_bRight;
	int mAttack1Time;

	int mTimeRun;

	bool onGround();
	//int sideStuck();

	bool m_bHeadStuck;
	bool m_bRun;
	bool m_bOnGround;
	bool m_bHit;
	int mCountHitTime;
	int mCountStamina;
	int mDyingTime;


	bool m_bSleep = true;

	void AnimationProcess();

	int HIT_TIME;
};

#endif

