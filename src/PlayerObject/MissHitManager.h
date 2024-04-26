//
// Take miss hit event and render it
//
#pragma once

#include <vector>
class MissHitManager
{
public:
	void takeMissHit();
	void renderMissHit();
	static MissHitManager* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new MissHitManager();
		}
		return s_pInstance;
	}
private:
	static MissHitManager* s_pInstance;
	int mCountTimeExist = 0;
};

