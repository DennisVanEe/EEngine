#include "ee_DataContainerEngine.hpp"

bool eeGames::DataContainerEngine::addContainer(const std::string &id)
{
	auto it = m_containerList.find(id);
	if (it == m_containerList.end()) // make sure it doesn't already exist
		return false;

	m_containerList.insert(std::make_pair(id, std::move(std::unique_ptr<DataContainer>(new DataContainer()))));
	return true;
}

bool eeGames::DataContainerEngine::loadContainer(const std::string &id, const std::string &dir)
{
	if (m_containerList.count(id) != 0) // make sure it doesn't already exist
		return false;

	auto it = m_containerList.insert(std::make_pair(id, std::move(std::unique_ptr<DataContainer>(new DataContainer()))));
	if (it.first->second->load_from_file(dir) == false)
	{
		m_containerList.erase(it.first);
		return false;
	}
	return true;
}

bool eeGames::DataContainerEngine::removeContainer(const std::string &id)
{
	auto it = m_containerList.find(id);
	if (it == m_containerList.end()) // if it can't find it
		return false;
	it->second.release();
	m_containerList.erase(it);
	return true;
}

bool eeGames::DataContainerEngine::saveContainer(const std::string &id, const std::string &dir) const
{
	auto it = m_containerList.find(id);
	if (it == m_containerList.end()) // if it can't find it
		return false;
	if (it->second->save_to_file(dir) == false)
		return false;
	return true;
}
