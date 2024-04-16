#ifndef SPELLOBJECT_H_
#define SPELLOBJECT_H_

#include "ObjectModel.h"

class SpellObject :
	public ObjectModel

#include "Animation.h"
{
public:
	SpellObject();
	virtual ~SpellObject();

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);
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
	virtual GameVector* getMapPosition()
	{
		return mMapPosition;
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
	}
protected:
	GameVector* mMapPosition;
	GameVector* mVelocity;
	GameVector* mAcceleration;

	Animation* mAnimation;

	SDL_RendererFlip mFlip;

	int mAttackRange;
	int ATK;
}

#endif //SPELLOBJECT_H_
