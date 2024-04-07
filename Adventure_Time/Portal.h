#ifndef PORTAL_H_
#define PORTAL_H_
#include "InteractObject.h"

class Portal :
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
	~Portal();
private:
	Portal();
	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);

	friend class PortalGenerator;
};

class PortalGenerator :
	public BaseGenerator
{
	BaseObject* generateObject() const
	{
		return new Portal();
	}
};
#endif //PORTAL_H_