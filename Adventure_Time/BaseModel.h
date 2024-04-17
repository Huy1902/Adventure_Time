#ifndef BASEMODEL_H_
#define BASEMODEL_H_
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


class BaseModel :
    public BaseObject
{
public:
	BaseModel();
	virtual ~BaseModel();
	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();

protected:
	GameVector* mPosition;
};

#endif

