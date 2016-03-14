#include "stdafx.h"
#include "ee_MusicCounter.hpp"

bool eeGames::MusicContainer::processContainer(thor::ResourceHolder<sf::Music, std::string>* holder)
{
	using namespace tinyxml2;

	XMLElement *entity = m_xmlFile.FirstChildElement()->FirstChildElement(); // go to the first Entity
	if (entity == nullptr) return false;

	while (entity != nullptr)
	{
		sf::Music &sound = holder->acquire(entity->Attribute("id"), thor::Resources::fromFile<sf::Music>(entity->Attribute("dir")), thor::Resources::Reuse);
		m_musicList.insert(std::make_pair(std::string(entity->Attribute("id")), sound));
		entity = entity->NextSiblingElement();
	}
	return true;
}
