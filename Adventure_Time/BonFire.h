#ifndef BONFIRE_H_
#define BONFIRE_H_
#include "InteractObject.h"


class BonFire :
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
	~BonFire();
private:
	BonFire();
	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);

	friend class BonFireGenerator;
};

class BonFireGenerator :
	public BaseGenerator
{
	BaseObject* generateObject() const
	{
		return new BonFire();
	}
};
#endif