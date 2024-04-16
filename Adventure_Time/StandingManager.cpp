#include "StandingManager.h"
#include <fstream>
#include <iostream>

using namespace std;

StandingManager* StandingManager::s_pInstance = nullptr;

void StandingManager::resetStanding()
{
	mStanding.clear();
	vector<int> output = getStandingPrivate();
	ofstream fout("score.txt");
	for (int i = 0; i < output.size(); ++i)
	{
		fout << output[i] << '\n';
		cout << output[i] << '\n';
	}
	fout.close();
}

std::vector<int> StandingManager::getStanding()
{
	return getStandingPrivate();
}

void StandingManager::updateScoreStanding()
{
	takeStanding("score_buffer.txt");
}

StandingManager::StandingManager()
{
	takeStanding("score.txt");
}

StandingManager::~StandingManager()
{

}

void StandingManager::takeStanding(const string& fileName)
{
	ifstream fin(fileName);
	int i;
	while (fin >> i)
	{
		mStanding.insert(i);
	}
	fin.close();
}

vector<int> StandingManager::getStandingPrivate()
{
	vector<int> ans;
	set<int>::iterator ite = mStanding.begin();
	if (mStanding.size() < 3)
	{
		for (const int& ite : mStanding)
		{
			ans.push_back(ite);
		}
		reverse(ans.begin(), ans.end());
		while (ans.size() < 3)
		{
			ans.push_back(0);
		}
	}
	else
	{
		while (ans.size() < 3)
		{
			ans.push_back(*ite);
			++ite;
		}
		reverse(ans.begin(), ans.end());
	}
	return ans;
}
