#ifndef ENEMYMODEL_H_
#define ENEMYMODEL_H_
#include "CharModel.h"

#include <SDL.h>
#include <vector>

#include "Animation.h"

class EnemyObject :
    public CharModel
{
public:
	EnemyObject();
	~EnemyObject();

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
	virtual int getHeight()const
	{
		return mCharHeight;
	}
	virtual int getCharWidth() const
	{
		return mCharWidth;
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
		return animation;
	}
	virtual int getDamage() const
	{
		return mStatus.ATK;
	}
	virtual void getHurt()
	{

	}
	virtual bool isAlive()
	{
		return mStatus.isAlive;
	}
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
protected:
	GameVector* mMapPosition;
	bool m_bSleep = true;
	int mWakeTime;

	bool sideStuck(EnemyObject* obj);

};

#endif

