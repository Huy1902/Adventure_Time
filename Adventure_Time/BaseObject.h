#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

//C++lin
#include <iostream>

//project file
#include "TextureLoader.h"
enum sound_type
{
	NONE = -1,
	MUSIC = 0,
	SFX = 1
};

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

struct Sound
{
	std::string filePath = "";
	sound_type type = NONE;
	std::string soundID = "";
};

class BaseObject
{
public:

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info) = 0;
	virtual void processData() = 0;
	virtual void renderObject() const = 0;
	virtual void clearObject() = 0;

protected:
	BaseObject() {};
	virtual ~BaseObject() {}
};

#endif BASEOBJECT_H_

