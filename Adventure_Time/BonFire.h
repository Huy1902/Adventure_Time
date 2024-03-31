#ifndef BONFIRE_H_
#define BONFIRE_H_
#include "ObjectModel.h"
#include "BaseGenerator.h"

class BonFire :
	public ObjectModel
{
public:
	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();

	GameVector* getPosition()
	{
		return mPosition;
	}
	void setPosition(const GameVector& obj)
	{
		*mPosition = obj;
	}
	void setMapPosition(const GameVector& obj)
	{
		*mMapPosition = obj;
	}
	int getWidth() const
	{
		return mWidth;
	}
	~BonFire();
private:
	BonFire();
	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);

	GameVector* mMapPosition;

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