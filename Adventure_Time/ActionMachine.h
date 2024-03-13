#pragma once

//C++ lib
#include <vector>

//project file
#include "BaseAction.h"

class ActionMachine
{
public:
	ActionMachine();
	void pushAction(BaseAction* pAction);
	void changeAction(BaseAction* pAction);
	void popAction();

	void processData();
	void renderAction();

private:
	std::vector<BaseAction*> mActions;

};

