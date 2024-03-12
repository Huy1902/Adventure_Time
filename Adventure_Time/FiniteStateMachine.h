#ifndef FINITESTATEMACHINE_H_
#define FINITESTATEMACHINE_H_

//C++ lib
#include <vector>

//project file
#include "BaseState.h"

class FiniteStateMachine
{
public:
	FiniteStateMachine();
	void pushState(BaseState* pState);
	void changeState(BaseState* pState);
	void popState();

	void processData();
	void renderState();

private:
	std::vector<BaseState*> mStates;

};

#endif // FINITESTATEMACHINE_H_
