#ifndef OBJECTMODEL_H_
#define OBJECTMODEL_H_

#include "BaseModel.h"

class ObjectModel :
	public BaseModel
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
	int mWidth;
	int mHeight;
	int mIndexFrames;
	int mNumFrames;
};

#endif

