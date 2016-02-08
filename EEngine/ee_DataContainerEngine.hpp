#pragma once

#include <unordered_map>

#include "ee_DataContainer.hpp"
#include "ee_DataType.hpp"

namespace eeGames
{
	class DataContainerEngine
	{
	private:
		std::unordered_map<std::string, DataContainer*> _m_containerList;
	public:
		bool addContainer(const std::string &_p_name);
		bool loadContainer(const std::string &_p_name, const std::string &_p_directory);
		bool removeContainer(const std::string &_p_name);
		bool saveContainer(const std::string &_p_name, const std::string &_p_directory) const;

		bool addData(const std::string &_p_name, DataType _p_dataType, const std::string &_p_dataName, byte *_p_data);
		byte *getData(const std::string &_p_name, const std::string &_p_dataName) const;
	};
}
