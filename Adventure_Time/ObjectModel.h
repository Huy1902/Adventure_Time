#ifndef OBJECTMODEL_H_
#define OBJECTMODEL_H_

#include <map>

#include "BaseObject.h"
#include "GameVector.h"


class ObjectModel :
	public BaseObject
{
public:
	ObjectModel();
	virtual ~ObjectModel();

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info);
	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();

protected:
	std::string mTextureID;
	GameVector* mPosition;
	int mWidth;
	int mHeight;
	int mIndexFrames;
	int mNumFrames;
};

#endif

