#ifndef ANIMODEL_H_
#define ANIMMODE_H
#include "BaseModel.h"

#include <vector>
#include <SDL.h>
#include <map>

#include "Animation.h"

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
class AnimModel :
    public BaseModel
{
public:
	AnimModel();
	virtual  ~AnimModel();

	virtual void processData();
	virtual void renderObject() const;
	virtual void clearObject();
	Animation* getAnimation()
	{
		return mAnimation;
	}
protected:
	std::map<std::string, Info> mActions;
	Animation* mAnimation;
	std::vector<Texture> mTextures;
	std::map<std::string, SFX> mSFXs;
};

#endif

