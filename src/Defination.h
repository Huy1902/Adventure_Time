#ifndef  DEFINATION_H_
#define	 DEFINATION_H_
#include <string>

struct Bar
{
	int x;
	int y;
	int w;
	int h;
	std::string textureID;
};
struct Info
{
	int w = 0;
	int h = 0;
	int numFrames = 0;
	int speed = 1;
	std::string textureID = "";
	int callbackID = -1;
	int x = 0;
	int y = 0;
};
struct Texture
{
	std::string filePath = "";
	std::string textureID = "";
};

struct SFX
{
	std::string filePath;
	std::string sfxID;
	int channel;
};
enum sound_type
{
	NONE = -1,
	MUSIC_SOUND = 0,
	SOUND_EFFECT = 1
};

struct Status
{
	int HP = 100;
	int STA = 20;
	int ATK = 20;
	int DEF = 5;
	int IQ = 10;
	int LUCK = 10;
	int EXP = 100;
	bool isAlive = true;
	bool isInvulnerable = false;
	bool isStunned = false;
};

#endif // ! DEFINATION_H_
