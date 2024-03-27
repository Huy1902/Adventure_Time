#pragma once
#include "ObjectModel.h"

#include <vector>
#include <map>

#include <SDL.h>

#include "Animation.h"


struct Status
{
	int HP = 100;
	int STA = 20;
	int ATK = 20;
	int DEF = 10;
	int IQ = 10;
	int LUCK = 10;
	int EXP = 100;
	bool isAlive = true;
	bool isInvulnerable = false;
	bool isStunned = false;
};
class CharModel :
	public ObjectModel
{
public:
	CharModel();
	virtual  ~CharModel();

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);
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
		STUN = 14
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
	std::map<std::string, Info> mActions;
	std::vector<Texture> mTextures;

	Animation* animation;
	Action mCurrentAction;
	SDL_RendererFlip mFlip;

	int mDyingTime;

	int mCountTimeHit = 0;
	int mCountAttack1 = 0;
	int mCountTimeAttack2 = 0;
	int mCountTimeDash = 0;
	int mCountTimeAttack1 = 0;
	int mCountTimeBash = 0;
	int mCountTimeCrit = 0;
};
