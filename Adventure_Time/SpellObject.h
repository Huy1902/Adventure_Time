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
	void setVelocity(const GameVector& obj)
	{
		*mVelocity = obj;
	}
	void setMapPosition(const GameVector& obj)
	{
		*mMapPosition = obj;
	}
	GameVector* getMapPosition()
	{
		return mMapPosition;
	}
	void setDitection(bool isRight)
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
	virtual bool isAttack() const
	{
		return false;
	}
	int getDamage() const
	{
		return ATK;
	}
	bool isExist()
	{
		if (mCountTimeExist > 0)
		{
			return true;
		}
		return false;
	}
protected:
	GameVector* mMapPosition;
	GameVector* mVelocity;
	//GameVector* mAcceleration;

	SDL_RendererFlip mFlip;
	int mAttackRange;
	int ATK;
	int mCooldown;

	int mCountTimeExist;

	enum Action
	{
		CAST = 0,
	};
	void cast();
};


#endif
