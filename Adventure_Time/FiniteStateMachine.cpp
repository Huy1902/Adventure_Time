#include "FiniteStateMachine.h"

#include <iostream>

#include "InputManager.h"
FiniteStateMachine::FiniteStateMachine()
{

}

void FiniteStateMachine::pushState(BaseState* pState)
{
	mStates.push_back(pState);
	mStates.back()->startState();
}

void FiniteStateMachine::changeState(BaseState* newState)
{
	m_bChange = true;
	pState = newState;
}

void FiniteStateMachine::popState()
{
	m_bPop = true;
}

void FiniteStateMachine::processData()
{
	if (mStates.empty() == false)
	{
		mStates.back()->processData();
	}
	if (m_bChange == true)
	{
		change();
		m_bChange = false;
	}
	if (m_bPop == true)
	{
		pop();
		m_bPop = false;
	}
}

void FiniteStateMachine::renderState()
{
	if (mStates.empty() == false)
	{
		mStates.back()->renderState();
	}
}

void FiniteStateMachine::pop()
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
void FiniteStateMachine::change()
{
	//std::cout << mStates.size();
	if (mStates.empty() == false)
	{
		if (mStates.back()->getStateID() != pState->getStateID())
		{
			while (mStates.empty() == false && mStates.back()->getStateID() != pState->getStateID())
			{
				if (mStates.back()->exitState())
				{
					delete mStates.back();
					mStates.pop_back();
				}
				else
				{
					std::cout << "Delete failed\n";
				}
			}
			//push new state
			mStates.push_back(pState);
			mStates.back()->startState();

		}
		else
		{
			std::cout << "State change is same as state before\n";
		}
	}
	InputManager::getInstance()->resetState();
}