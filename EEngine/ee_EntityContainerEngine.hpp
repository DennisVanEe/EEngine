#pragma once

#include <string>
#include <fstream>
#include <iostream>

#include "ee_EntityContainer.hpp"
#include "ee_KeyedData.hpp"

namespace eeGames
{
	class EntityContainerEngine
	{
	private:
		KeyedData<std::string, EntityContainer> m_containers;
	public:
		EntityContainerEngine() {}

		bool loadContainer(const std::string &id, const std::string &dir)
		{
			auto pair = m_containers.insert(std::make_pair(id, EntityContainer()));
			if (pair.second == false)
			{
				std::cout << "[ERROR]: could not insert EntityContainer " << id << " into list\n";
				return false;
			}
			return pair.first->second.loadContainer(dir);
		}
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