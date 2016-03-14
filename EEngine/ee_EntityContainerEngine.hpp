#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <Thor\Resources.hpp>

#include "ee_EntityContainer.hpp"
#include "ee_KeyedData.hpp"

namespace eeGames
{
	class EntityContainerEngine
	{
	private:
		KeyedData<std::string, EntityContainer> m_containers;
		thor::ResourceHolder<sf::Texture, std::string> m_textResource;

	public:
		EntityContainerEngine() {}

		bool loadContainer(const std::string &id, const std::string &dir);
		bool removeContainer(const std::string &id)
		{
			auto it = m_containers.find(id);
			if (it == m_containers.end())
				return false;
			m_containers.erase(it);
			return true;
		}

		bool exists(const std::string &id)
		{
			auto it = m_containers.find(id);
			return it != m_containers.end();
		}

		// used by the entity constructor
		bool getEntityFormCont(const std::string &contID, const std::string &entID, void *memory) const
		{
			auto it = m_containers.find(contID);
			if (it == m_containers.end())
				return false;
			if (it->second.getEntity(entID, memory) == false)
				return false;
			return true;
		}
	};
}