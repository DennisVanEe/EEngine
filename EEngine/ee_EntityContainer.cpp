#include "ee_EntityContainer.hpp"

bool eeGames::EntityContainer::processContainer(thor::ResourceHolder<sf::Texture, std::string> *holder)
{
	using namespace tinyxml2;

	XMLElement *entity = m_xmlFile.FirstChildElement()->FirstChildElement(); // go to the first Entity
	XMLElement *entProperty = nullptr;
	if (entity == nullptr) return false;

	while (entity != nullptr)
	{
		if (std::string(entity->Attribute("type")) == "animated") // create an entity for animated type
		{
			AnimatedEntity *temp = new AnimatedEntity();
			entProperty = entity->FirstChildElement(); if (entProperty == nullptr) return false;
			sf::Texture &temp = holder->acquire(entProperty->Attribute("id"), thor::Resources::fromFile<sf::Texture>(entProperty->Attribute("dir")));

			entProperty = entProperty->NextSiblingElement(); if (entProperty == nullptr) return false;

			m_allCurrentEntities.insert(std::make_pair(entity->Attribute("id"), new AnimatedEntity()));
		}
	}

	return false;
}
