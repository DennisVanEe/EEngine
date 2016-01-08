#include "stdafx.h"
#include "Level.hpp"

// Level methods:

eeGames::Level::Level(const eeContainer<Entity> & entities, const eeContainer<ScriptedEntity> & scripted, const std::string & mod, const std::string & stepFuncDir) : 
	entityContainer(entities), scriptedEntityContainer(scripted), module(mod)
{
	// load the stepFunction (controller file)
	std::ifstream ifs(stepFuncDir);
	stepScript.assign((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));

	scriptEngine.loadLevelScript(*this); // load the level 
}

void eeGames::Level::setUpForRendering()
{
	std::vector<std::string> tempEnt = entityContainer.getNameList();
	std::vector<std::string> tempScr = scriptedEntityContainer.getNameList();

	for (std::string n : tempEnt)
		renderEntitities.push_back(&entityContainer.getObject(n));
	for (std::string n : tempScr)
		renderEntitities.push_back(&scriptedEntityContainer.getObject(n));

	std::sort(renderEntitities.begin(), renderEntitities.end(), lessThanPtrComp);
}


