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
		KeyedData<std::wstring, EntityContainer> m_containers;
	public:
		EntityContainerEngine() {}

		bool loadContainer(const std::wstring &id, const std::string &dir)
		{
			auto pair = m_containers.insert(std::make_pair(id, EntityContainer()));
			if (pair.second == false)
			{
				std::wcout << L"[ERROR]: could not insert EntityContainer " << id << L" into list\n";
				return false;
			}
			return pair.first->second.loadContainer(dir);
		}
		bool removeContainer(const std::wstring &id)
		{
			auto it = m_containers.find(id);
			if (it == m_containers.end())
				return false;
			m_containers.erase(it);
			return true;
		}

		bool getEntityFormCont(const std::wstring &contID, const std::wstring &entID, void *memory) const
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