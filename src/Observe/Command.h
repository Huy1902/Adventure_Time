#pragma once
class Command
{
public:
	virtual void execute()
	{

	}
};


class DefeatEnemyCommand :
	public Command
{
public:
	virtual void execute();
};

class FirstBossCommand :
	public Command
{
public:
	virtual void execute();
};

class MissCommand :
	public Command
{
public:
	virtual void execute();
};