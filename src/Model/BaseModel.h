#ifndef BASEMODEL_H_
#define BASEMODEL_H_
#include "BaseObject.h"

#include "GameVector.h"
#include "BaseGenerator.h"
#include "Defination.h"

class BaseModel :
    public BaseObject
{
public:
	BaseModel();
	virtual ~BaseModel();
	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();

	GameVector* getPosition()
	{
		return mPosition;
	}
	void setPosition(const GameVector& pos)
	{
		*mPosition = pos;
	}
protected:
	GameVector* mPosition;
};

#endif

