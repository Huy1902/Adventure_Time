#ifndef BASESTATE_H_
#define BASESTATE_H_

#include <string>
#include <vector>

#include "ObjectModel.h"

class BaseState
{
public:
	virtual void processData() = 0;
	virtual void renderState() = 0;

	virtual bool startState() = 0;
	virtual bool exitState() = 0;
	
	virtual std::string getStateID() const = 0;

protected:
	std::vector<ObjectModel*> mObjects;
	std::vector<std::string> mTextureID;

	typedef void(*callback)();
};

#endif //BASESTATE_H_
