#pragma once

#include <memory>
#include <unordered_map>

#include "ee_DataContainer.hpp"

namespace eeGames
{
	class DataContainerEngine
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<DataContainer>> m_containerList;
	public:
		bool addContainer(const std::string &id);
		bool loadContainer(const std::string &id, const std::string &dir);
		bool removeContainer(const std::string &id);
		bool saveContainer(const std::string &id, const std::string &dir) const;

		bool exists(const std::string &id)
		{
			auto it = m_containerList.find(id);
			return it != m_containerList.end();
		}

		// TODO: return false if it already exists
		template<typename T>
		bool add_int(const std::string &c_name, const std::string &d_name, T data)
		{
			auto it = m_containerList.find(c_name);
			if (it == m_containerList.end())
				return false;
			it->second->add_int(d_name, data);
		}
		template<typename T>
		bool add_float(const std::string &c_name, const std::string &d_name, T data)
		{
			auto it = m_containerList.find(c_name);
			if (it == m_containerList.end())
				return false;
			it->second->add_float(d_name, data);
		}
		bool add_string(const std::string &c_name, const std::string &d_name, const std::string &data)
		{
			auto it = m_containerList.find(c_name);
			if (it == m_containerList.end())
				return false;
			it->second->add_string(d_name, data);
		}

		template<typename T>
		bool get_num(const std::string &c_name, const std::string &d_name, T *data) const
		{
			auto it = m_containerList.find(c_name);
			if (it == m_containerList.end())
				return false;

			return it->second->get_num(d_name, data);
		}
		bool get_string(const std::string &c_name, const std::string &d_name, std::string *data) const
		{
			auto it = m_containerList.find(c_name);
			if (it == m_containerList.end())
				return false;

			return it->second->get_string(d_name, data);
		}
	};
}
