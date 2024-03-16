#ifndef PLAYEROBJECT_H_
#define PLAYEROBJECT_H_
#include "ObjectModel.h"

class PlayerObject :
    public ObjectModel
{
public:
	PlayerObject();
	~PlayerObject();

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
	void setVelocity(const GameVector& obj)
	{
		*mVelocity = obj;
	}
	void setVelocityX(const double& val)
	{
		mVelocity->setX(val);
	}
private:
	bool m_bOnAir;


	GameVector* mVelocity;
	GameVector* mAcceleration;

	bool m_bRight;


	std::map<std::string, ActionModel*> mActionMap;
	ActionModel* mCurrentAction;
};

#endif
