#include "FiniteStateMachine.h"

#include <iostream>

FiniteStateMachine::FiniteStateMachine()
{

}

void FiniteStateMachine::pushState(BaseState* pState)
{
	mStates.push_back(pState);
	mStates.back()->startState();
}

void FiniteStateMachine::changeState(BaseState* pState)
{
	if (mStates.empty() == false)
	{
		if (mStates.back()->getStateID() != pState->getStateID())
		{
			if (mStates.back()->exitState())
			{
				delete mStates.back();
				mStates.pop_back();
				
				//push new state
				mStates.push_back(pState);
				mStates.back()->startState();
			}
			else
			{
				std::cout << "Delete failed\n";
			}
		}
		else
		{
			std::cout << "State change is same as state before\n";
		}
	}
}

void FiniteStateMachine::popState()
{
	if (mStates.empty() == false)
	{
		if (mStates.back()->exitState())
		{
			delete mStates.back();
			mStates.pop_back();
		}
	}
}

void FiniteStateMachine::processData()
{
	if (mStates.empty() == false)
	{
		mStates.back()->processData();
	}
}

void FiniteStateMachine::renderState()
{
	if (mStates.empty() == false)
	{
		mStates.back()->renderState();
	}
}