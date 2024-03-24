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
	void parserAction(const std::string& filePath, std::map<std::string, Info>& actionMap, std::vector<Texture>& textureVector);

	void parserButton(const std::string& filePath, std::vector<Info>& buttonMap, std::vector<Texture>& textureVector);
	static ObjectParser* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new ObjectParser();
		}
		return s_pInstance;
	}

	void parserTexture(const std::string& filePath, std::vector<Texture>& textureVector);
private:
	static ObjectParser* s_pInstance;

	ObjectParser();
	~ObjectParser();

	void loadTexture(std::vector<Texture>& textureVector, XmlNode* textures);
	void loadAction(std::map<std::string, Info>& actionMap, XmlNode* actions);
	void loadButton(std::vector<Info>& buttonMap, XmlNode* buttons);
	void loadAnimation(std::vector<Info>& animMap, XmlNode* anims);
};

#endif

