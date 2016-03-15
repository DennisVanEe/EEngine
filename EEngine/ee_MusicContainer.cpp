#include "stdafx.h"
#include "ee_MusicContainer.hpp"

bool eeGames::MusicContainer::processContainer()
{
	using namespace tinyxml2;

	XMLElement *entity = m_xmlFile.FirstChildElement()->FirstChildElement(); // go to the first Entity
	if (entity == nullptr) return false;

	while (entity != nullptr)
	{
		auto pair = m_musicList.insert(std::make_pair(std::string(entity->Attribute("id")), std::move(SoundMusic())));
		if (pair.first->second.assignSoundMusic(entity->Attribute("dir")) == false)
			throw std::runtime_error("music buffer was null");
		entity = entity->NextSiblingElement();
	}
	return true;
}
