#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

//C++lin
#include <iostream>

//project file
#include "TextureLoader.h"

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

