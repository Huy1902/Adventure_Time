#include "ActionMachine.h"

#include <iostream>

ActionMachine::ActionMachine()
{

}

void ActionMachine::pushAction(BaseAction* pAction)
{
	mActions.push_back(pAction);
	mActions.back()->onEnter();
}

void ActionMachine::changeAction(BaseAction* pAction)
{
	if (mActions.empty() == false)
	{
		if (mActions.back()->getActionID() != pAction->getActionID())
		{
			if (mActions.back()->onExit())
			{
				delete mActions.back();
				mActions.pop_back();

				//push new Action
				mActions.push_back(pAction);
				mActions.back()->onEnter();
			}
			else
			{
				std::cout << "Delete failed\n";
			}
		}
		else
		{
			std::cout << "Aciton change is same as Action before\n";
		}
	}
}

void ActionMachine::popAction()
{
	if (mActions.empty() == false)
	{
		if (mActions.back()->onExit())
		{
			delete mActions.back();
			mActions.pop_back();
		}
	}
}

void ActionMachine::processData()
{
	if (mActions.empty() == false)
	{
		mActions.back()->processData();
	}
}

void ActionMachine::renderAction()
{
	if (mActions.empty() == false)
	{
		mActions.back()->renderAction();
	}
}