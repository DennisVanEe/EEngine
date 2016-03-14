#include "ee_EntityContainer.hpp"

bool eeGames::EntityContainer::processContainer(thor::ResourceHolder<sf::Texture, std::string> *holder)
{
	using namespace tinyxml2;

	XMLElement *entity = m_xmlFile.FirstChildElement()->FirstChildElement(); // go to the first Entity
	XMLElement *entProperty = nullptr;
	if (entity == nullptr) return false;

	while (entity != nullptr)
	{
		std::string type(entity->Attribute("type"));
		if (type == "animated") // create an entity for animated type
		{
			AnimatedEntity *temp = new AnimatedEntity();

			entProperty = entity->FirstChildElement(); if (entProperty == nullptr) return false;
			sf::Texture &texture = holder->acquire(entProperty->Attribute("id"), thor::Resources::fromFile<sf::Texture>(entProperty->Attribute("dir")), thor::Resources::Reuse);

			entProperty = entProperty->NextSiblingElement(); if (entProperty == nullptr) return false;
			temp->assignTexture(&texture, entProperty->IntAttribute("columns"), entProperty->IntAttribute("rows"), entProperty->IntAttribute("frames"));

			m_allCurrentEntities.insert(std::make_pair(std::string(entity->Attribute("id")), std::unique_ptr<Entity>(temp)));
		}
		else if (type == "static")
		{
			StaticEntity *temp = new StaticEntity();

			entProperty = entity->FirstChildElement(); if (entProperty == nullptr) return false;
			sf::Texture &texture = holder->acquire(entProperty->Attribute("id"), thor::Resources::fromFile<sf::Texture>(entProperty->Attribute("dir")), thor::Resources::Reuse);
		
			if (entProperty->IntAttribute("width") == 0 || entProperty->IntAttribute("height") == 0)
			{
				temp->assignTexture(&texture);
			}
			else
			{
				temp->assignTexture(&texture, entProperty->IntAttribute("x"), entProperty->IntAttribute("y"), entProperty->IntAttribute("width"), entProperty->IntAttribute("height"));
			}
			m_allCurrentEntities.insert(std::make_pair(std::string(entity->Attribute("id")), std::unique_ptr<Entity>(temp)));
		}
		entity = entity->NextSiblingElement();
	}
	return true;
}
