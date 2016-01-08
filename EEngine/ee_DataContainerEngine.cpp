#include "ee_DataContainerEngine.hpp"

bool eeGames::DataContainerEngine::add_container(const std::string &name)
{
	if (containers.count(name) != 0) // make sure it doesn't already exist
		return false;

	DataContainer *temp_cont = new DataContainer();
	containers[name] = temp_cont;
	return true;
}

bool eeGames::DataContainerEngine::load_container(const std::string &name, const std::string &dir)
{
	if (containers.count(name) != 0) // make sure it doesn't already exist
		return false;

	DataContainer *temp_cont = new DataContainer();
	if (temp_cont->load_from_file(dir) == false)
		return false;
	containers[name] = temp_cont;
	return true;
}

bool eeGames::DataContainerEngine::remove_container(const std::string &name)
{
	auto it = containers.find(name);
	if (it == containers.end()) // if it can't find it
		return false;
	delete it->second;
	containers.erase(it);
	return true;
}

bool eeGames::DataContainerEngine::save_container(const std::string &name, const std::string &dir) const
{
	auto it = containers.find(name);
	if (it == containers.end()) // if it can't find it
		return false;
	it->second->save_to_file(dir);
	return true;
}

bool eeGames::DataContainerEngine::add_data(const std::string &name, DataType type, const std::string &d_name, byte *data)
{
	auto it = containers.find(name);
	if (it == containers.end())
		return false;

	switch (type)
	{
	case DataType::INT:
		it->second->add_int(d_name, *reinterpret_cast<int*>(data));
		break;
	case DataType::FLOAT:
		it->second->add_float(d_name, *reinterpret_cast<float*>(data));
		break;
	case DataType::DOUBLE:
		it->second->add_double(d_name, *reinterpret_cast<double*>(data));
		break;
	case DataType::STRING:
		it->second->add_string(d_name, std::string(data));
		break;
	case DataType::BOOL:
		it->second->add_bool(d_name, *reinterpret_cast<bool*>(data));
		break;
	}
	return true;
}

eeGames::byte *eeGames::DataContainerEngine::get_data(const std::string &name, const std::string &d_name) const
{
	auto it = containers.find(name);
	if (it == containers.end())
		return nullptr;
	
	return it->second->get_data(d_name);
}