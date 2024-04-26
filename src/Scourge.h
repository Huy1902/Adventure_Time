#ifndef SCOURGE_H_
#define SCOURGE_H_
#include "SpellObject.h"
#include "BaseGenerator.h"

class Scourge :
	public SpellObject
{
public:
	
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
		if (mAnimation->getIndexFrame() == 6)
		{
			return true;
		}
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

private:
	Scourge();
	friend class ScourgeGenerator;
};

class ScourgeGenerator :
	public BaseGenerator
{
	BaseObject* generateObject() const
	{
		return new Scourge();
	}
};

#endif //SCOURGE_H_