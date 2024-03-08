#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

//C++lin
#include <iostream>

//project file
#include "TextureLoader.h"

class GameObject
{
public:

	virtual void loadTexture(std::unique_ptr<TextureLoader> Info) = 0;
	virtual void processData() = 0;
	virtual void renderObject() const = 0;
	virtual void cleanObject() = 0;

protected:
	GameObject() {};
	virtual ~GameObject() {}
};

#endif GAMEOBJECT_H_

