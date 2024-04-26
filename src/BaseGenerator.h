#ifndef BASEGENERATOR_H_
#define BASEGENERATOR_H_

#include "BaseObject.h"

class BaseGenerator
{
public:
	virtual BaseObject* generateObject() const = 0;
	virtual ~BaseGenerator() {}
};

#endif
