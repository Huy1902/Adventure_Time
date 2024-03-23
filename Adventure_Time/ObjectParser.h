#ifndef OBJECTPARSER_H_
#define OBJECTPARSER_H_

#include <map>
#include<string>
#include <vector>
#include"XmlTree.h"
struct Info;

struct Texture;

class ObjectParser
{
public:
	void parser(const std::string& filePath, std::map<std::string, Info>& objectMap, std::vector<Texture>& textureVector);
	static ObjectParser* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new ObjectParser();
		}
		return s_pInstance;
	}
private:
	static ObjectParser* s_pInstance;

	ObjectParser();
	~ObjectParser();
};

#endif

