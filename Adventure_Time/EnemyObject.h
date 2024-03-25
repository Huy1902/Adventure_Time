#ifndef ENEMYMODEL_H_
#define ENEMYMODEL_H_
#include "ObjectModel.h"

#include <SDL.h>
#include <vector>

#include "Animation.h"

class EnemyObject :
    public ObjectModel
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
		if (mAttack1Time % 10 == 0)
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
	virtual bool getDying()
	{
		return m_bDying;
	}
protected:

	GameVector* mVelocity;
	GameVector* mAcceleration;

	GameVector* mMapPosition;

	int mCharHeight = 64;
	int mCharWidth = 64;


	enum Action
	{
		RUN = 0,
		IDLE = 2,
		FALL = 3,
		WAKE_UP = 4,
		ATTACK1 = 5,
		HIT = 6,
		ATTACK2 = 7,
		DYING = 8
	};
	bool m_bDying = true;
	int mDyingTime = 0;
	Action mCurrentAction;

	Status mStatus;

	Animation* animation;

	SDL_RendererFlip mFlip;

	std::map<std::string, Info> mActions;

	std::vector<Texture> mTextures;

	void run();
	void none();
	void wake();
	void attack1();
	void hit();
	void attack2();
	void dying();

	bool sideStuck(EnemyObject* obj);
private:
	int mAttack1Time;
};

#endif

