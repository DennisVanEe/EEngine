#pragma once

#include <memory>
#include <string>
#include <tinyxml2.h>
#include <Thor\Resources.hpp>

#include "ee_AnimatedEntity.hpp"
#include "ee_StaticEntity.hpp"
#include "ee_KeyedData.hpp"
#include "ee_Algorithms.hpp"

namespace eeGames
{
	class EntityContainer
	{
	private:
		KeyedData<std::string, std::unique_ptr<Entity>> m_allCurrentEntities;
		tinyxml2::XMLDocument m_xmlFile; // the xml file for defining the entities
	public:
		EntityContainer() {}
		EntityContainer(const EntityContainer& ent) = delete;
		EntityContainer& operator=(const EntityContainer& ent) = delete;

		bool loadContainer(const std::string &dir)
		{
			using namespace tinyxml2;

			XMLError error = m_xmlFile.LoadFile(dir.c_str());
			if (error != XML_SUCCESS)
			{
				std::cout << "[ERROR]: problem loading or parsing xml file at: " << dir << L"\n";
				return false;
			}
			return true;
		}
		bool processContainer(thor::ResourceHolder<sf::Texture, std::string> *holder);

		// used by the constructor to get a copy
		bool getEntity(const std::string &id, void *ent) const
		{
			auto it = m_allCurrentEntities.find(id);
			if (it == m_allCurrentEntities.end())
				return false;
			switch (it->second->getType())
			{
			case EntityType::ANIMATED:
				*static_cast<AnimatedEntity*>(ent) = *static_cast<AnimatedEntity*>(it->second.get());
				return true;
			case EntityType::STATIC:
				*static_cast<StaticEntity*>(ent) = *static_cast<StaticEntity*>(it->second.get());
				return true;
			default:
				throw std::runtime_error("unknown entity type was accessed");
				return false;
			}
		}
	};
}
