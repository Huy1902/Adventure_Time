#pragma once
#include "ObjectModel.h"

enum Interact_Type
{
	NOTHING = -1,
	SAVE_POINT = 0,
	COIN = 1
};
class InteractObject :
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
	virtual void setPosition(const GameVector& obj)
	{
		*mPosition = obj;
	}
	virtual void setMapPosition(const GameVector& obj)
	{
		*mMapPosition = obj;
	}
	virtual GameVector* getMapPosition()
	{
		return mMapPosition;
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
	InteractObject();
	virtual ~InteractObject();
protected:
	Interact_Type mType;
	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);

	GameVector* mMapPosition;

	bool m_bAbleToInteract;
};

