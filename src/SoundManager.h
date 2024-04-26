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

	void playMusic(const std::string& id, int loop);

	void playSound(const std::string& id, int loop, int channel);

	bool isMutedMusic()
	{
		return m_bMuteMusic;
	}
	bool isMutedSFX()
	{
		return m_bMuteSFX;
	}

	void muteMusic();
	void muteSFX();

	void enableMusic()
	{
		if (Mix_PausedMusic() == true)
		{
			Mix_ResumeMusic();
		}
		m_bMuteMusic = false;
	}
	void enableSFX()
	{
		m_bMuteSFX = false;
	}

	void clearMusic(const std::string& id);
	void clearSFX(const std::string& id);

private:
	static SoundManager* s_pInstance;

	std::map<std::string, Mix_Chunk*> mSfxs;
	std::map<std::string, Mix_Music*> mMusic;

	int m_bMuteMusic = false;
	int m_bMuteSFX = false;

	SoundManager();
	~SoundManager();
};

typedef SoundManager TheSoundManager;

#endif

