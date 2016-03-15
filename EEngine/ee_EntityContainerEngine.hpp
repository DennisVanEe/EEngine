#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <Thor\Resources.hpp>
#include <unordered_map>

#include "ee_EntityContainer.hpp"

namespace eeGames
{
	class EntityContainerEngine
	{
	private:
		std::unordered_map<std::string, EntityContainer> m_containers;
		thor::ResourceHolder<sf::Texture, std::string> m_textResource;

	public:
		EntityContainerEngine() {}

		void loadContainer(const std::string &id, const std::string &dir);
		void removeContainer(const std::string &id)
		{
			auto it = m_containers.find(id);
			if (it == m_containers.end())
				throw std::logic_error("could not find the entity container " + id);
			m_containers.erase(it);
		}

		bool exists(const std::string &id)
		{
			auto it = m_containers.find(id);
			return it != m_containers.end();
		}

		// used by the entity constructor
		void getEntityFormCont(const std::string &contID, const std::string &entID, void *memory) const
		{
			auto it = m_containers.find(contID);
			if (it == m_containers.end())
			{
				std::cout << "could not find the entity container\n";
				throw std::logic_error("could not find the entity container " + contID);
			}
			it->second.getEntity(entID, memory);
		}
	};
}