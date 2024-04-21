#include "SpellStream.h"

#include <algorithm>

#include "SpellManager.h"
#include "InputManager.h"

SpellStream* SpellStream::s_pInstance = nullptr;

using namespace std;

void SpellStream::update()
{
	vector<string> needErase;
	for (auto& ite : mSkillOnCooldown)
	{
		if (ite.second > 0)
		{
			--ite.second;
		}
		else
		{
			needErase.push_back(ite.first);
		}
	}
	for (const auto& ite : needErase)
	{
		mSkillOnCooldown.erase(ite);
	}
}

void SpellStream::changeKey(const std::string& skill, SDL_Scancode keyChange)
{
	SDL_Scancode oldKey;
	for (const auto& ite : mKeyToSkill)
	{
		if (ite.second == skill)
		{
			oldKey = ite.first;
		}
	}
	std::string oldSkill = mKeyToSkill[keyChange];
	mKeyToSkill[oldKey] = oldSkill;
	mKeyToSkill[keyChange] = skill;
}

void SpellStream::changeSkill(const std::string& skillChange, SDL_Scancode key)
{
	std::string oldSkill = mKeyToSkill[key];
	SDL_Scancode oldKey;
	for (const auto& ite : mKeyToSkill)
	{
		if (ite.second == skillChange)
		{
			oldKey = ite.first;
		}
	}
	mKeyToSkill[oldKey] = oldSkill;
	mKeyToSkill[key] = skillChange;
}

void SpellStream::skillStreamer(const GameVector& pos, const bool& isRight)
{
	for (const auto& ite : mKeyToSkill)
	{
		if (InputManager::getInstance()->keyDown(ite.first) == true && mSkillOnCooldown.find(ite.second) == mSkillOnCooldown.end())
		{
			mSkillOnCooldown[ite.second] = mSkillCooldown[ite.second];
			SpellManager::getInstance()->addPlayerSpell(ite.second, pos, isRight);
		}
	}
}

void SpellStream::addSkill(const std::string& skillName, SDL_Scancode key, const int& cooldownTime)
{
	mKeyToSkill[key] = skillName;
	mSkillCooldown[skillName] = cooldownTime;
}

