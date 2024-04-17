#ifndef SCOURGE_H_
#define SCOURGE_H_
#include "SpellObject.h"


class Scourge :
	public SpellObject
{
public:
	Scourge();
	virtual ~Scourge();

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
		return false;
	}
	virtual Animation* getAnimation()
	{
		return mAnimation;
	}
	virtual int getDamage() const
	{
		return ATK;
	}
protected:
};


#endif //SCOURGE_H_