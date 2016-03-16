#pragma once

#include <memory>
#include <string>
#include <tinyxml2.h>
#include <unordered_map>
#include <Thor\Resources.hpp>
#include <iostream>

#include "ee_AnimatedEntity.hpp"
#include "ee_StaticEntity.hpp"
#include "ee_Algorithms.hpp"
#include "ee_XMLContainer.hpp"

namespace eeGames
{
	class EntityContainer : public XMLDocument
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<Entity>> m_allCurrentEntities;

	public:
		EntityContainer() {}

		EntityContainer(const EntityContainer& ent) = delete;
		EntityContainer& operator=(const EntityContainer& ent) = delete;
		
		EntityContainer(EntityContainer &&other) : 
			m_allCurrentEntities(std::move(other.m_allCurrentEntities))
		{
		}

		void processContainer(thor::ResourceHolder<sf::Texture, std::string> *holder);

		// used by the constructor to get a copy
		void getEntity(const std::string &id, void *ent) const
		{
			auto it = m_allCurrentEntities.find(id);
			if (it == m_allCurrentEntities.end())
			{
				std::cout << "could not find the entity " << id << "\n";
				throw std::logic_error("could not find the entity " + id);
			}

			EntityType type = it->second->getType();
			switch (it->second->getType())
			{
			case EntityType::ANIMATED:
				*static_cast<AnimatedEntity*>(ent) = *static_cast<AnimatedEntity*>(it->second.get());
				break;
			case EntityType::STATIC:
				*static_cast<StaticEntity*>(ent) = *static_cast<StaticEntity*>(it->second.get());
				break;
			default:
				throw std::runtime_error("unknown entity type was accessed");
			}
		}
	};
}
