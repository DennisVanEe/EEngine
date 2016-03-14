#include "stdafx.h"
#include "ee_MusicContainer.hpp"

bool eeGames::MusicContainer::processContainer(thor::ResourceHolder<sf::Music, std::string>* holder)
{
	using namespace tinyxml2;

	XMLElement *entity = m_xmlFile.FirstChildElement()->FirstChildElement(); // go to the first Entity
	if (entity == nullptr) return false;

	while (entity != nullptr)
	{
		sf::Music &sound = holder->acquire(entity->Attribute("id"), thor::Resources::fromFile<sf::Music>(entity->Attribute("dir")), thor::Resources::Reuse);
		auto pair = m_musicList.insert(std::make_pair(std::string(entity->Attribute("id")), SoundMusic()));
		if (pair.first->second.assignSoundMusic(&sound) == false) 
			throw std::runtime_error("music buffer was null");
		entity = entity->NextSiblingElement();
	}
	return true;
}
