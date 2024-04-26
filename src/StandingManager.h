#pragma once
#include <set>
#include <vector>
#include <string>
class StandingManager
{
public:
	void resetStanding();
	std::vector<int> getStanding();
	static StandingManager* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new StandingManager();
		}
		return s_pInstance;
	}

	void updateScoreStanding();

private:
	StandingManager();
	~StandingManager();
	static StandingManager* s_pInstance;
	std::set<int> mStanding;

	void takeStanding(const std::string & fileName);
	std::vector<int> getStandingPrivate();
};

