#include "stdafx.h"
#include "LoadingEngine.hpp"

bool eeGames::LoadingEngine::checkXMLError(tinyxml2::XMLError result)
{
	if (result != tinyxml2::XML_SUCCESS)
	{
		std::cout << result << std::endl;
		return false;
	}
}

bool eeGames::LoadingEngine::load(const std::string & RXMLD, const std::string & LXMLD)
{
	// load files
	if (resourceXML.LoadFile(RXMLD.c_str()) != tinyxml2::XML_SUCCESS)
	{
		std::cout << "[error]: issue parsing or opening resource xml file\n";
		return false;
	}
	if (levelXML.LoadFile(LXMLD.c_str()) != tinyxml2::XML_SUCCESS)
	{
		std::cout << "[error]: issue parsing or opening load xml file\n";
		return false;
	}

	// access the first element of resource
	tinyxml2::XMLElement* resElement = resourceXML.FirstChildElement()->FirstChildElement();
	
	assert(resElement != nullptr); // check if it loaded properly

	while (resElement != nullptr)
	{
		if (std::string(resElement->Attribute("type")) == "texture")
		{
			textureContainer.addObject(resElement->Attribute("name"), Resource<sf::Texture>(resElement->Attribute("dir")));
		}

		/*
		else if (std::string(resElement->Attribute("type")) == "sound_buffer")
		{
			soundBufferContainer.addObject(resElement->Attribute("name"),
				Resource<sf::SoundBuffer>(resElement->Attribute("dir")));
		}
		*/

		resElement = resElement->NextSiblingElement();
	}

	// access the first element of level
	tinyxml2::XMLElement* level = levelXML.FirstChildElement()->FirstChildElement();
	tinyxml2::XMLElement* entity;

	assert(level != nullptr); // check if it loaded properly

	while (level != nullptr)
	{
		eeContainer<Entity> entityContainer;
		eeContainer<ScriptedEntity> scriptedEntityContainer;

		entity = level->FirstChildElement()->FirstChildElement();

		while (entity != nullptr)
		{
			// load all of the entity values:
			std::string name = entity->Attribute("name");
			const Resource<sf::Texture> & texture = textureContainer.getConstObject(entity->Attribute("texture"));
			_COL_TYPE col_type = static_cast<_COL_TYPE>(entity->IntAttribute("col_type"));
			bool light = entity->IntAttribute("light");
			bool staticMov = entity->IntAttribute("static");

			sf::Vector2f pos = sf::Vector2f(entity->FirstChildElement()->FloatAttribute("x"), entity->FirstChildElement()->FloatAttribute("x"));
			sf::Vector2f org = sf::Vector2f(entity->FirstChildElement()->NextSiblingElement()->FloatAttribute("x"),
				entity->FirstChildElement()->NextSiblingElement()->FloatAttribute("y"));
			int zPos = entity->FirstChildElement()->IntAttribute("zPos");

			if (entity->IntAttribute("script"))
			{
				// load the script file:
				std::string scriptDir = entity->FirstChildElement()->NextSiblingElement()->NextSiblingElement()->Attribute("dir");
				scriptedEntityContainer.addObject(name, ScriptedEntity(texture, pos, org, zPos, col_type, light, stat,
					scriptDir));
			}
			else
				entityContainer.addObject(name, Entity(texture, pos, org, zPos, col_type, light, stat));

			entity = entity->NextSiblingElement();
		}

		// load the level
		levelContainer.addObject(level->Attribute("name"), Level(entityContainer, scriptedEntityContainer,
			std::string(level->Attribute("name")) + ".as", level->Attribute("stepDir")));

		level = level->NextSiblingElement();
	}

	loaded = true;

	return true;
}
