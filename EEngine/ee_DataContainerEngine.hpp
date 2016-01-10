#pragma once

#include <unordered_map>

#include "ee_DataContainer.hpp"
#include "ee_DataType.hpp"

namespace eeGames
{
	class DataContainerEngine
	{
	private:
		std::unordered_map<std::string, DataContainer*> containers;
	public:
		bool add_container(const std::string &name);
		bool load_container(const std::string &name, const std::string &dir);
		bool remove_container(const std::string &name);
		bool save_container(const std::string &name, const std::string &dir) const;

		bool add_data(const std::string &name, DataType type, const std::string &d_name, byte *data);
		byte *get_data(const std::string &name, const std::string &d_name) const;
	};
}
