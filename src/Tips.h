#ifndef TIPS_H_
#define TIPS_H_

#include <string>
class Tips
{
public:
	void loadTip();
	void exitTip();
	void renderTip(int x, int y);
	static Tips* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new Tips();
		}
		return s_pInstance;
	}
private:
	static Tips* s_pInstance;

	std::string mTip;

	Tips();
	~Tips();
};

#endif //TIPS_H_

