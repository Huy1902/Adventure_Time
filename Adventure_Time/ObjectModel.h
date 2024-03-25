#ifndef OBJECTMODEL_H_
#define OBJECTMODEL_H_

#include <map>

#include "BaseObject.h"
#include "GameVector.h"
#include "ActionModel.h"

struct Status
{
	int HP = 100;
	int STA = 20;
	int ATK = 20;
	int DEF = 10;
	int IQ = 10;
	int LUCK = 10;
	int EXP = 100;
	bool isAlive = true;
	bool isInvulnerable = false;
};
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

	virtual Status* getStatus()
	{
		return &mStatus;
	}

protected:
	std::string mTextureID;
	GameVector* mPosition;
	int mWidth;
	int mHeight;
	int mIndexFrames;
	int mNumFrames;
	double mScope;

	Status mStatus;
};

#endif

