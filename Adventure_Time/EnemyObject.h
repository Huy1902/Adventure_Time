#ifndef ENEMYMODEL_H_
#define ENEMYMODEL_H_
#include "ObjectModel.h"

#include <SDL.h>

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
	int getHeight()const
	{
		return mCharHeight;
	}
	int getCharWidth() const
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
protected:

	GameVector* mVelocity;
	GameVector* mAcceleration;

	GameVector* mMapPosition;

	int mCharHeight = 64;
	int mCharWidth = 64;

	SDL_RendererFlip mFlip;
};

#endif

