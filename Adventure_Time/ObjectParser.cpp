#include "ObjectParser.h"
#include <iostream>

ObjectParser* ObjectParser::s_pInstance = nullptr;
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
enum sound_type
{
	NONE = -1,
	MUSIC = 0,
	SFX = 1
};

struct Sound
{
	std::string filePath = "";
	int type = -1;
	std::string soundID = "";
};

struct Bar
{
	int x;
	int y;
	int w;
	int h;
	std::string textureID;
};




void ObjectParser::parserTexture(const std::string& filePath, std::vector<Texture>& textureVector)
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

	loadTexture(textureVector, textures);
}

void ObjectParser::parserCharacter(const std::string& filePath, std::map<std::string, Info>& actionMap, std::vector<Texture>& textureVector, std::vector<Sound>& soundVector)
{
}

void ObjectParser::parserBar(const std::string& filePath, std::map<std::string, Bar>& barMap, std::vector<Texture>& textureVector)
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

	loadTexture(textureVector, textures);


	XmlNode* bars = nullptr;
	for (XmlNode* ite : root->child)
	{
		if (ite->element == std::string("BARS"))
		{
			bars = ite;
			break;
		}
	}
	loadBar(barMap, bars);
}

ObjectParser::ObjectParser()
{

}

ObjectParser::~ObjectParser()
{

}

void ObjectParser::loadTexture(std::vector<Texture>& textureVector, XmlNode* textures)
{
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
}

void ObjectParser::loadAction(std::map<std::string, Info>& actionMap, XmlNode* actions)
{
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
			actionMap[name] = obj;
			//cout << name << ' ' << obj.w << ' ' << obj.h << ' ' << obj.textureID << ' ' << obj.numFrames << ' ' << obj.speed << '\n';
		}
	}
}

void ObjectParser::loadButton(std::vector<Info>& buttonMap, XmlNode* buttons)
{
	if (buttons != nullptr)
	{
		for (XmlNode* button : buttons->child)
		{
			Info obj;
			/*std::string name = "";
			button->takeAttribute("name", &name);*/
			button->takeAttribute("w", &obj.w);
			button->takeAttribute("h", &obj.h);
			button->takeAttribute("textureID", &obj.textureID);
			button->takeAttribute("numFrame", &obj.numFrames);
			button->takeAttribute("callbackID", &obj.callbackID);
			button->takeAttribute("x", &obj.x);
			button->takeAttribute("y", &obj.y);
			if (button->takeAttribute("speed", &obj.speed) == false)
			{
				obj.speed = 1;
			}
			buttonMap.push_back(obj);
			//cout << name << ' ' << obj.w << ' ' << obj.h << ' ' << obj.textureID << ' ' << obj.numFrames << ' ' << obj.speed << '\n';
		}
	}
}

void ObjectParser::loadAnimation(std::vector<Info>& animMap, XmlNode* anims)
{
	if (anims != nullptr)
	{
		for (XmlNode* anim : anims->child)
		{
			Info obj;
			/*std::string name = "";
			button->takeAttribute("name", &name);*/
			anim->takeAttribute("w", &obj.w);
			anim->takeAttribute("h", &obj.h);
			anim->takeAttribute("textureID", &obj.textureID);
			anim->takeAttribute("numFrame", &obj.numFrames);
			anim->takeAttribute("x", &obj.x);
			anim->takeAttribute("y", &obj.y);
			if (anim->takeAttribute("speed", &obj.speed) == false)
			{
				obj.speed = 1;
			}
			animMap.push_back(obj);
			//cout << name << ' ' << obj.w << ' ' << obj.h << ' ' << obj.textureID << ' ' << obj.numFrames << ' ' << obj.speed << '\n';
		}
	}
}

void ObjectParser::loadSound(std::vector<Sound>& soundVector, XmlNode* sounds)
{
	if (sounds != nullptr)
	{
		for (XmlNode* sound : sounds->child)
		{
			Sound obj;

			soundVector.push_back(obj);
			//cout << name << ' ' << obj.w << ' ' << obj.h << ' ' << obj.textureID << ' ' << obj.numFrames << ' ' << obj.speed << '\n';
		}
	}
}

void ObjectParser::loadBar(std::map<std::string, Bar>& barMap, XmlNode* bars)
{
	if (bars != nullptr)
	{
		for (XmlNode* bar : bars->child)
		{
			Bar obj;
			std::string name = "";
			bar->takeAttribute("name", &name);
			bar->takeAttribute("w", &obj.w);
			bar->takeAttribute("h", &obj.h);
			bar->takeAttribute("textureID", &obj.textureID);
			bar->takeAttribute("x", &obj.x);
			bar->takeAttribute("y", &obj.y);

			barMap[name] = obj;
		}
	}
}

void ObjectParser::parserAction(const std::string& filePath, std::map<std::string, Info>& actionMap, std::vector<Texture>& textureVector)
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

	loadTexture(textureVector, textures);
	

	XmlNode* actions = nullptr;
	for (XmlNode* ite : root->child)
	{
		if (ite->element == std::string("ACTIONS"))
		{
			actions = ite;
			break;
		}
	}
	loadAction(actionMap, actions);
}

void ObjectParser::parserButton(const std::string& filePath, std::vector<Info>& buttonMap, std::vector<Texture>& textureVector)
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
	loadTexture(textureVector, textures);


	XmlNode* buttons = nullptr;
	for (XmlNode* ite : root->child)
	{
		if (ite->element == std::string("BUTTONS"))
		{
			buttons = ite;
			break;
		}
	}
	loadButton(buttonMap, buttons);
}
