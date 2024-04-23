#ifndef CHARMODEL_H_
#define CHARMODEL_H_

#include "AnimModel.h"

class CharModel :
	public AnimModel
{
public:
	CharModel();
	virtual  ~CharModel();

	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();

	virtual Status* getStatus()
	{
		return &mStatus;
	}
	virtual Status* getMaxStatus()
	{
		return &MaxStatus;
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
protected:

	Status mStatus;
	Status MaxStatus;

	GameVector* mVelocity;
	GameVector* mAcceleration;


	int mCharHeight;
	int mCharWidth;

	enum Action
	{
		RUN = 0,
		JUMP = 1,
		IDLE = 2,
		FALL = 3,
		ATTACK1 = 4,
		HURT = 5,
		LANDING = 6,
		DASH = 7,
		DYING = 8,
		ATTACK2 = 9,
		WAKE_UP = 10,
		HIT = 11,
		BASH = 12,
		CRIT = 13,
		STUN = 14,
		FLY = 15
	};


	void run();
	void jump();
	void idle();
	void fall();
	void attack1();
	void hurt();
	void landing();
	void dash();
	void dying();
	void none();
	void wake();
	void hit();
	void attack2();
	void bash();
	void crit();
	void stun();


	Action mCurrentAction;
	SDL_RendererFlip mFlip;

	int mDyingTime;
	int mCountTimeHit = 0;
	int mCountTimeAttack2 = 0;
	int mCountTimeDash = 0;
	int mCountTimeAttack1 = 0;
	int mCountTimeBash = 0;
	int mCountTimeCrit = 0;
	int mCountTimeRun = 0;
	int mCountTimeStun = 0;
	int mCountTimeHurt = 0;
	int mCountTimeAbleToCrit = 0;
	int mCountTimeLanding = 0;
	int mCountStamina = 0;

	bool m_bHeadStuck = false;
	bool m_bOnGround = false;
};

#endif //CHARMODEL_H_