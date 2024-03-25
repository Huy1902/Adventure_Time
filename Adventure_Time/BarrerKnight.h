#ifndef BARRERKNIGHT_H_
#define BARRERKNIGHT_H_
#include "EnemyObject.h"

#include <SDL.h>

#include <vector>


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
		if ( (mCurrentAction == ATTACK1 && (animation->getIndexFrame() == 4) ) || (mCurrentAction == ATTACK2 && animation->getIndexFrame() == 5))
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

	BarrerKnight();
	~BarrerKnight();



private:

	GameVector* mVelocity;
	GameVector* mAcceleration;

	GameVector mSavePosition;

	Animation* animation;
	SDL_RendererFlip mFlip;
	int mAttackTine;

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
	bool m_bHit;
	int mCountHitTime;

	int mCountStamina;

	bool m_bSleep = true;

	void AnimationProcess();



	void run();
	void none();
	void wakeUp();
	void attack1();
	void hit();
	void attack2();

	std::map<std::string, Info> actions;
	std::vector<Texture> textureVector;
};

#endif

