#ifndef OBJECTMODEL_H_
#define OBJECTMODEL_H_

#include <map>

#include "BaseObject.h"
#include "GameVector.h"
#include "ActionModel.h"

class ObjectModel :
	public BaseObject
{
public:
	ObjectModel();
	~ObjectModel();

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);
	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();

protected:
	std::string mTextureID;

	GameVector mPosition;
	GameSize mSize;
	GameVector mVelocity;
	GameVector mAcceleration;
	
	bool m_bRight;
	int mIndexFrames;
	int mNumFrames;
	double mScope;

	std::map<std::string, ActionModel*> mActionMap;
	ActionModel* mCurrentAction;
};

#endif

