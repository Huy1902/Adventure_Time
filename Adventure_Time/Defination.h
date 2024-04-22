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




#endif // ! DEFINATION_H_
