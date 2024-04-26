#ifndef SPELLSTREAM_H_
#define SPELLSTREAM_H_

#include <map>
#include <string>
#include <vector>
#include <SDL.h>

#include "GameVector.h"

#include "Defination.h"

class SpellStream
{
public:
	void update();
	void changeKey(const std::string& skill, SDL_Scancode keyChange);
	void changeSkill(const std::string& skillChange, SDL_Scancode key);
	void skillStreamer(const GameVector& pos, const bool & isRight);
	void addSkill(const std::string& skillName, SDL_Scancode key, const int& cooldownTime);
	void renderSpellMenu();
	static SpellStream* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new SpellStream();
		}
		return s_pInstance;
	}
private:
	static SpellStream* s_pInstance;

	SpellStream();

	std::map<SDL_Scancode, std::string>  mKeyToSkill;
	std::map<std::string, int> mSkillCooldown;
	std::map<std::string, int> mSkillOnCooldown;
	std::map<std::string, Bar> mSkill;
	std::vector<Texture> mTextures;
};

#endif