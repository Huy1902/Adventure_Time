#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include <map>
#include <string>
#include "SDL_mixer.h"

enum sound_type;

//Need a singleton because every music and sound should be saved at one place and can be accessed from anywhere of the program
class SoundManager
{
public:
	static SoundManager* getInstance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new SoundManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool loadSound(std::string  fileName, std::string  id, sound_type type);

	void playMusic(std::string  id, int loop);

	void playSound(std::string id, int loop, int channel);


private:
	static SoundManager* s_pInstance;

	std::map<std::string , Mix_Chunk*> mSfxs;
	std::map<std::string , Mix_Music*> mMusic;

	SoundManager();
	~SoundManager();
};

typedef SoundManager TheSoundManager;

#endif

