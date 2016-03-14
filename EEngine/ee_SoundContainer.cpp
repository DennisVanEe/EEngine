#include "ee_SoundContainer.hpp"

bool eeGames::SoundContainer::processContainer(thor::ResourceHolder<sf::SoundBuffer, std::string>* holder)
{
	using namespace tinyxml2;

	XMLElement *entity = m_xmlFile.FirstChildElement()->FirstChildElement(); // go to the first Entity
	if (entity == nullptr) return false;

	while (entity != nullptr)
	{
		sf::SoundBuffer &sound = holder->acquire(entity->Attribute("id"), thor::Resources::fromFile<sf::SoundBuffer>(entity->Attribute("dir")), thor::Resources::Reuse);
		auto pair = m_soundBuffers.insert(std::make_pair(std::string(entity->Attribute("id")), SoundEffect()));
		if (pair.first->second.assignSoundBuffer(&sound) == false)
			throw std::runtime_error("sound buffer was null");
		entity = entity->NextSiblingElement();
	}
	return true;
}
