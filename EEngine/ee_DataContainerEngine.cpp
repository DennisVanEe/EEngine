#include "ee_DataContainerEngine.hpp"

bool eeGames::DataContainerEngine::add_container(const std::string &name)
{
	if (_containerList.count(name) != 0) // make sure it doesn't already exist
		return false;

	_containerList[name] = std::unique_ptr<DataContainer>(new DataContainer());
	return true;
}

bool eeGames::DataContainerEngine::load_container(const std::string &name, const std::string &dir)
{
	if (_containerList.count(name) != 0) // make sure it doesn't already exist
		return false;

	auto it = _containerList.insert(std::make_pair(name, std::unique_ptr<DataContainer>(new DataContainer)));
	if (it.first->second->load_from_file(dir) == false)
	{
		_containerList.erase(it.first);
		return false;
	}
	return true;
}

bool eeGames::DataContainerEngine::remove_container(const std::string &name)
{
	auto it = _containerList.find(name);
	if (it == _containerList.end()) // if it can't find it
		return false;
	delete it->second.release();
	_containerList.erase(it);
	return true;
}

bool eeGames::DataContainerEngine::save_container(const std::string &name, const std::string &dir) const
{
	auto it = _containerList.find(name);
	if (it == _containerList.end()) // if it can't find it
		return false;
	if (it->second->save_to_file(dir) == false)
		return false;
	return true;
}
