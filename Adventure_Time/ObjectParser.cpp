#include "ObjectParser.h"
#include <iostream>

using namespace std;

ObjectParser* ObjectParser::s_pInstance = nullptr;
struct Info
{
	int w = 0;
	int h = 0;
	int numFrames = 0;
	int speed = 1;
	std::string textureID = "";
};

struct Texture
{
	std::string filePath = "";
	std::string textureID = "";
};


ObjectParser::ObjectParser()
{

}

ObjectParser::~ObjectParser()
{

}

void ObjectParser::parser(const std::string& filePath, std::map<std::string, Info>& objectMap, std::vector<Texture>& textureVector)
{
	XmlTree tree;
	tree.parseXmlFile(filePath);
	XmlNode* root = tree.getRoot();

	XmlNode* textures = nullptr;
	for (XmlNode* ite : root->child)
	{
		if (ite->element == std::string("TEXTURES"))
		{
			textures = ite;
			break;
		}
	}
	if (textures != nullptr)
	{
		for (XmlNode* texture : textures->child)
		{
			Texture obj;
			texture->takeAttribute("filePath", &obj.filePath);
			texture->takeAttribute("textureID", &obj.textureID);
			textureVector.push_back(obj);
			//cout << obj.filePath << ' ' << obj.textureID << '\n';
		}
	}

	XmlNode* actions = nullptr;
	for (XmlNode* ite : root->child)
	{
		if (ite->element == std::string("ACTIONS"))
		{
			actions = ite;
			break;
		}
	}
	if (actions != nullptr)
	{
		for (XmlNode* action : actions->child)
		{
			Info obj;
			std::string name = "";
			action->takeAttribute("name", &name);
			action->takeAttribute("w", &obj.w);
			action->takeAttribute("h", &obj.h);
			action->takeAttribute("textureID", &obj.textureID);
			action->takeAttribute("numFrame", &obj.numFrames);
			if (action->takeAttribute("speed", &obj.speed) == false)
			{
				obj.speed = 1;
			}
			objectMap[name] = obj;
			//cout << name << ' ' << obj.w << ' ' << obj.h << ' ' << obj.textureID << ' ' << obj.numFrames << ' ' << obj.speed << '\n';
		}
	}
}