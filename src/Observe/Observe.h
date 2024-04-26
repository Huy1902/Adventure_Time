#pragma once

#include "Command.h"

class Observe
{
public:
	void takeCommand(Command* command)
	{
		command->execute();
		delete command;
	}
	static Observe* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new Observe();
		}
		return s_pInstance;
	}
private:
	static Observe* s_pInstance;
};

