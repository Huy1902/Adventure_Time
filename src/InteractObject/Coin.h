#ifndef COIN_H_
#define COIN_H_
#include "InteractObject.h"

class Coin :
	public InteractObject
{
public:
	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();

	GameVector* getPosition()
	{
		return mPosition;
	}
	virtual void setPosition(const GameVector& obj)
	{
		*mPosition = obj;
	}
	virtual void setMapPosition(const GameVector& obj)
	{
		*mMapPosition = obj;
	}
	virtual int getWidth() const
	{
		return mWidth;
	}
	virtual bool interactItem();
	virtual Interact_Type getType() const
	{
		return mType;
	}
	virtual GameVector* getMapPosition()
	{
		return mMapPosition;
	}
	virtual ~Coin();
private:
	Coin();
	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);

	friend class CoinGenerator;
};

class CoinGenerator :
	public BaseGenerator
{
	BaseObject* generateObject() const
	{
		return new Coin();
	}
};

#endif

