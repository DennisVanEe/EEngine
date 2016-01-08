#include "stdafx.h"
#include "ScriptedEntity.hpp"

eeGames::ScriptedEntity::ScriptedEntity(const Resource<sf::Texture> & t, const sf::Vector2f & pos, const sf::Vector2f & org, int zPos, _COL_TYPE type, bool light, bool stat, 
	const std::string& scptDir) : Entity(t, pos, org, zPos, type, light, stat)
{
	loadScript(scptDir);
}

void eeGames::ScriptedEntity::loadScript(const std::string& dir)
{
	std::ifstream ifs(dir);
	scriptFile.assign((std::istreambuf_iterator<char>(ifs)),
		(std::istreambuf_iterator<char>()));
}
