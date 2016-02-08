#include "ee_DataContainerEngine.hpp"

bool eeGames::DataContainerEngine::addContainer(const std::string &_p_name)
{
	if (_m_containerList.count(_p_name) != 0) // make sure it doesn't already exist
		return false;

	DataContainer *temp_cont = new DataContainer();
	_m_containerList[_p_name] = temp_cont;
	return true;
}

bool eeGames::DataContainerEngine::loadContainer(const std::string &_p_name, const std::string &_p_directory)
{
	if (_m_containerList.count(_p_name) != 0) // make sure it doesn't already exist
		return false;

	DataContainer *temp_cont = new DataContainer();
	if (temp_cont->load_from_file(_p_directory) == false)
		return false;
	_m_containerList[_p_name] = temp_cont;
	return true;
}

bool eeGames::DataContainerEngine::removeContainer(const std::string &_p_name)
{
	auto it = _m_containerList.find(_p_name);
	if (it == _m_containerList.end()) // if it can't find it
		return false;
	delete it->second;
	_m_containerList.erase(it);
	return true;
}

bool eeGames::DataContainerEngine::saveContainer(const std::string &_p_name, const std::string &_p_directory) const
{
	auto it = _m_containerList.find(_p_name);
	if (it == _m_containerList.end()) // if it can't find it
		return false;
	it->second->save_to_file(_p_directory);
	return true;
}

bool eeGames::DataContainerEngine::addData(const std::string &_p_name, DataType _p_dataType, const std::string &_p_dataName, byte *_p_data)
{
	auto it = _m_containerList.find(_p_name);
	if (it == _m_containerList.end())
		return false;

	switch (_p_dataType)
	{
	case DataType::INT:
		it->second->add_int(_p_dataName, *reinterpret_cast<int*>(_p_data));
		break;
	case DataType::FLOAT:
		it->second->add_float(_p_dataName, *reinterpret_cast<float*>(_p_data));
		break;
	case DataType::DOUBLE:
		it->second->add_double(_p_dataName, *reinterpret_cast<double*>(_p_data));
		break;
	case DataType::STRING:
		it->second->add_string(_p_dataName, std::string(_p_data));
		break;
	case DataType::BOOL:
		it->second->add_bool(_p_dataName, *reinterpret_cast<bool*>(_p_data));
		break;
	}
	return true;
}

eeGames::byte *eeGames::DataContainerEngine::getData(const std::string &_p_name, const std::string &_p_dataName) const
{
	auto it = _m_containerList.find(_p_name);
	if (it == _m_containerList.end())
		return nullptr;
	
	return it->second->get_data(_p_dataName);
}