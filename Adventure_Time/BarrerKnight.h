#ifndef BARRERKNIGHT_H_
#define BARRERKNIGHT_H_
#include "EnemyObject.h"

#include <SDL.h>

class BarrerKnight :
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
		if (mAttack1Time % 10 == 0)
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
		return mStatus.DMG;
	}
	virtual void getHurt(const int& dmg);
	virtual bool isAlive()
	{
		return mStatus.isAlive;
	}

	BarrerKnight();
	~BarrerKnight();



private:

	GameVector* mVelocity;
	GameVector* mAcceleration;

	GameVector mSavePosition;

	Animation* animation;
	SDL_RendererFlip mFlip;
	int mAttackTine;
	Status mStatus;

	bool m_bRight;
	int mAttack1Time;


	int mCharHeight;
	int mCharWidth;

	int mTimeRun;

	bool onGround();
	//int sideStuck();

	bool m_bHeadStuck;
	bool m_bRun;
	bool m_bOnGround;

	int mCoolDownAttack1;
	
	

	void AnimationProcess();



	void run();
	void none();
	void wakeUp();
	void attack1();
};

#endif

