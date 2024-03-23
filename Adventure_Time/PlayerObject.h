#ifndef PLAYEROBJECT_H_
#define PLAYEROBJECT_H_
#include "ObjectModel.h"

#include <SDL.h>

#include "Animation.h"


class PlayerObject :
    public ObjectModel
{
public:
	PlayerObject();
	~PlayerObject();

	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();

	GameVector* getVelocity() 
	{
		return mVelocity;
	}
	GameVector* getPosition()
	{
		return mPosition;
	}
	void setPosition(const GameVector& obj)
	{
		*mPosition = obj;
	}
	void setPositionX(const double& val)
	{
		mPosition->setX(val);
	}
	void setPositionY(const double& val)
	{
		mPosition->setY(val);
	}
	void setVelocity(const GameVector& obj)
	{
		*mVelocity = obj;
	}
	void setVelocityX(const double& val)
	{
		mVelocity->setX(val);
	}
	void setVelocityY(const double& val)
	{
		mVelocity->setY(val);
	}
	int getHeight()const 
	{
		return mCharHeight;
	}
	int getCharWidth() const
	{
		return mCharWidth;
	}
	bool isAttack() const
	{
		if (mCurrentAction == ATTACK1 && mTimeAttack == 3)
		{
			return true;
		}
		return false;
	}
	bool isRight() const
	{
		if (mFlip == SDL_FLIP_NONE)
		{
			return true;
		}
		return false;
	}
	void getHurt(const int& damage);
	int getDamage() const
	{
		return mStatus.DMG;
	}
private:
	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);

	GameVector* mVelocity;
	GameVector* mAcceleration;

	bool m_bRight;


	int mCharHeight;
	int mCharWidth;

	bool onGround();
	bool headStuck();
	int sideStuck();

	bool m_bHeadStuck;
	bool m_bJump;
	bool m_bRun;
	bool m_bOnGround;
	bool m_bAttack;
	int mTimeAttack;
	int mLandingTime;
	int mTimeDash;
	int mCooldownDash;
	bool m_bDying;
	bool m_bHurting;
	int mCountTimeDying;
	int mCountTimeHurt;
	Status mStatus;

	SDL_RendererFlip mFlip;

	void AnimationProcess();

	enum Action
	{
		RUN = 0,
		JUMP = 1,
		IDLE = 2,
		FALL = 3,
		ATTACK1 = 4,
		HURT = 5,
		LANDING = 6,
		DASH = 7

	};

	Action mCurrentAction;
	Action mBackAction;

	Animation* animation;

	void run();
	void jump();
	void idle();
	void fall();
	void attack1();
	void hurt();
	void landing();
	void dash();
	void dying();
};

#endif
