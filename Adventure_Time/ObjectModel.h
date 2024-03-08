#ifndef OBJECTMODEL_H_
#define OBJECTMODEL_H_

#include "GameObject.h"
#include "GameVector.h"

class ObjectModel :
    public GameObject
{
public:
	ObjectModel();
	~ObjectModel();

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);
	virtual void processData();
	virtual void renderObject() const;
	virtual void cleanObject();

protected:
	std::string mTextureID;

	GameVector mPosition;
	GameSize mSize;

	int mIndexFrames;
	int mNumFrames;
	float mScope;
};

#endif

