#pragma once

#include <memory>

#include "ee_DataContainer.hpp"
#include "ee_KeyedData.hpp"

namespace eeGames
{
	class DataContainerEngine
	{
	private:
		KeyedData<std::string, std::unique_ptr<DataContainer>> _containerList;
	public:
		bool add_container(const std::string &);
		bool load_container(const std::string &, const std::string &);
		bool remove_container(const std::string &);
		bool save_container(const std::string &, const std::string &) const;

		// TODO: return false if it already exists
		template<typename T>
		bool add_int(const std::string &c_name, const std::string &d_name, T data)
		{
			auto it = _containerList.find(c_name);
			if (it == _containerList.end())
				return false;
			it->second->add_int(d_name, data);
		}
		template<typename T>
		bool add_float(const std::string &c_name, const std::string &d_name, T data)
		{
			auto it = _containerList.find(c_name);
			if (it == _containerList.end())
				return false;
			it->second->add_float(d_name, data);
		}
		bool add_string(const std::string &c_name, const std::string &d_name, const std::string &data)
		{
			auto it = _containerList.find(c_name);
			if (it == _containerList.end())
				return false;
			it->second->add_string(d_name, data);
		}

		template<typename T>
		bool get_num(const std::string &c_name, const std::string &d_name, T *data) const
		{
			auto it = _containerList.find(c_name);
			if (it == _containerList.end())
				return false;

			return it->second->get_num(d_name, data);
		}
		bool get_string(const std::string &c_name, const std::string &d_name, std::string *data) const
		{
			auto it = _containerList.find(c_name);
			if (it == _containerList.end())
				return false;

			return it->second->get_string(d_name, data);
		}
	};
}
