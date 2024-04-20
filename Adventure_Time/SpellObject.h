#ifndef SPELLOBJECT_H_
#define SPELLOBJECT_H_

#include "AnimModel.h"


class SpellObject :
	public AnimModel
{
public:
	SpellObject();
	virtual ~SpellObject();
	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();
	virtual bool isAttack() const
	{
		return false;
	}

	GameVector* getVelocity()
	{
		return mVelocity;
	}
	void setVelocity(const GameVector& obj)
	{
		*mVelocity = obj;
	}
	GameVector* getMapPosition()
	{
		return mMapPosition;
	}
	void setMapPosition(const GameVector& obj)
	{
		*mMapPosition = obj;
	}
	void setDirection(bool isRight)
	{
		if (isRight == false)
		{
			mFlip = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			mFlip = SDL_FLIP_NONE;
		}
	}
	bool isRight() const
	{
		if (mFlip == SDL_FLIP_NONE)
		{
			return true;
		}
		return false;
	}
	int getDamage() const
	{
		return ATK;
	}
	bool isExist() const
	{
		if (mCountTimeExist > 0)
		{
			return true;
		}
		return false;
	}
	int getCastDistance() const
	{
		return mCastDistance;
	}
protected:
	GameVector* mMapPosition;
	GameVector* mVelocity;

	SDL_RendererFlip mFlip;
	int mAttackRange;
	int mCastDistance;
	int ATK;
	int mCooldown;

	int mCountTimeExist;

	enum Action
	{
		CAST = 0,
	};
	Action mCurrentAction;
	void completeUpdateMethod();
	void AnimationProcess();
	void cast();
	
};


#endif
