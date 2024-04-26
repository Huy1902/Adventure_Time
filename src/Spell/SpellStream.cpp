#include "SpellStream.h"

#include <algorithm>

#include "SpellManager.h"
#include "InputManager.h"
#include "TextureManager.h"
#include "GameManager.h"
#include "ObjectParser.h"
SpellStream* SpellStream::s_pInstance = nullptr;

using namespace std;

const int W_LAYER = 67;
const int H_LAYER = 73;

void SpellStream::update()
{
	for (auto& ite : mSkillOnCooldown)
	{
		if (ite.second > 0)
		{
			--ite.second;
		}
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
		if (InputManager::getInstance()->keyDown(ite.first) == true && mSkillOnCooldown[ite.second] == 0)
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
	mSkillOnCooldown[skillName] = 0;
}

void SpellStream::renderSpellMenu()
{
	TextureManager::getInstance()->drawSinglePic("spell_menu", 50, 650, 210, 100, GameManager::getInstance()->getRenderer());
	for (const auto& ite : mSkill)
	{
		Bar temp = ite.second;
		int w = int(1.0 * mSkillOnCooldown[ite.first] / mSkillCooldown[ite.first] * temp.w);
		TextureManager::getInstance()->drawSinglePic(temp.textureID, temp.x, temp.y, w, temp.h, GameManager::getInstance()->getRenderer());
	}
}

SpellStream::SpellStream()
{
	ObjectParser::getInstance()->parserBar("spell_menu.xml", mSkill, mTextures);

	for (const auto& ite : mTextures)
	{
		TextureManager::getInstance()->load(ite.filePath, ite.textureID, GameManager::getInstance()->getRenderer());
	}

}

