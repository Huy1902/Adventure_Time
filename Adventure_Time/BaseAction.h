#ifndef BASEACTION_H_
#define BASEACTION_H_

#include <string>

#include "GameVector.h"

class BaseAction
{
public:
	virtual void processData() = 0;
	virtual void renderAction() = 0;
	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;
	virtual std::string getActionID() const = 0;
};

#endif

