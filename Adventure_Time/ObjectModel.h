#ifndef OBJECTMODEL_H_
#define OBJECTMODEL_H_

#include <map>

#include "BaseObject.h"
#include "GameVector.h"
#include "BaseGenerator.h"

struct Info
{
	int w = 0;
	int h = 0;
	int numFrames = 0;
	int speed = 1;
	std::string textureID = "";
	int callbackID = -1;
	int x = 0;
	int y = 0;
};
struct Texture
{
	std::string filePath = "";
	std::string textureID = "";
};


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

