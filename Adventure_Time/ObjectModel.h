#ifndef OBJECTMODEL_H_
#define OBJECTMODEL_H_

#include "GameObject.h"

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

	int mIndexFrames;
	int mXPos;
	int mYPos;
	int mWidth;
	int mHeight;
	int mNumFrames;
	double mScope;
};

#endif

