#include "ee_EntityContainer.hpp"

void eeGames::EntityContainer::processContainer(thor::ResourceHolder<sf::Texture, std::string> *holder)
{
	using namespace tinyxml2;

	XMLElement *entity = m_xmlFile.FirstChildElement()->FirstChildElement(); // go to the first Entity
	XMLElement *entProperty = nullptr;
	if (entity == nullptr)
		throw std::logic_error("Entity container xml file is not formatted properly");

	while (entity != nullptr)
	{
		std::string type(entity->Attribute("type"));
		if (type == "animated") // create an entity for animated type
		{
			AnimatedEntity *temp = new AnimatedEntity();

			entProperty = entity->FirstChildElement(); 
			if (entProperty == nullptr)
			{
				std::cout << "Entity container xml file is not formatted properly\n";
				throw std::logic_error("Entity container xml file is not formatted properly");
			}
	
			sf::Texture &texture = holder->acquire(entProperty->Attribute("id"), thor::Resources::fromFile<sf::Texture>(entProperty->Attribute("dir")), thor::Resources::Reuse);

			entProperty = entProperty->NextSiblingElement(); 
			if (entProperty == nullptr)
			{
				std::cout << "Entity container xml file is not formatted properly\n";
				throw std::logic_error("Entity container xml file is not formatted properly");
			}
			temp->assignTexture(&texture, entProperty->IntAttribute("columns"), entProperty->IntAttribute("rows"), entProperty->IntAttribute("frames"));
			temp->setFrameTime(entProperty->IntAttribute("time"));

			m_allCurrentEntities.insert(std::make_pair(std::move(std::string(entity->Attribute("id"))), std::move(std::unique_ptr<Entity>(temp))));
		}
		else if (type == "static")
		{
			StaticEntity *temp = new StaticEntity();

			entProperty = entity->FirstChildElement(); 
			if (entProperty == nullptr) 
				throw std::logic_error("Entity container xml file is not formatted properly");
			sf::Texture &texture = holder->acquire(entProperty->Attribute("id"), thor::Resources::fromFile<sf::Texture>(entProperty->Attribute("dir")), thor::Resources::Reuse);
		
			if (entProperty->IntAttribute("width") == 0 || entProperty->IntAttribute("height") == 0)
			{
				temp->assignTexture(&texture);
			}
			else
			{
				temp->assignTexture(&texture, entProperty->IntAttribute("x"), entProperty->IntAttribute("y"), entProperty->IntAttribute("width"), entProperty->IntAttribute("height"));
			}

			m_allCurrentEntities.insert(std::make_pair(std::move(std::string(entity->Attribute("id"))), std::move(std::unique_ptr<Entity>(temp))));
		}
		entity = entity->NextSiblingElement();
	}
}
