#ifndef VIDEOPLAYER_H_
#define VIDEOPLAYER_H_

#include <string>
class VideoPlayer
{
public:
	static VideoPlayer* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new VideoPlayer();
		}
		return s_pInstance;
	}
	void setFilePath(const std::string& s, int numFrames, const std::string& music);
	void updateFrame();
	void renderFrame();
private:
	static VideoPlayer* s_pInstance;
	std::string mFilePath;
	int mIndexFrame = 0;
	int mNumFrames = 0;
	int mSize = 0;
	VideoPlayer();
	~VideoPlayer();
};

#endif //VIDEOPLAYER_H_

