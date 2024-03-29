#ifndef GENERATORMANAGER_H_
#define GENERATORMANAGER_H_
#include <map>
#include <string>

#include "BaseGenerator.h"
class GeneratorManager
{
public:
	bool addGenerator(const std::string generatorID, BaseGenerator* generator)
	{
		if (mGeneratorMap.find(generatorID) != mGeneratorMap.end())
		{
			delete generator;
			return false;
		}
		mGeneratorMap[generatorID] = generator;
		return true;
	}
	BaseObject* generatorObject(const std::string generatorID)
	{
		auto ite = mGeneratorMap.find(generatorID);

		if (ite == mGeneratorMap.end())
		{
			return nullptr;
		}
		return (*ite).second->generateObject();
	}
	static GeneratorManager* getInstance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new GeneratorManager();
		}
		return s_pInstance;
	}
private:
	static GeneratorManager* s_pInstance;
	std::map<std::string, BaseGenerator*> mGeneratorMap;
};

#endif