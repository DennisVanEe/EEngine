#include "ee_EntityContainerEngine.hpp"

bool eeGames::EntityContainerEngine::loadContainer(const std::string & id, const std::string & dir)
{
	auto pair = m_containers.insert(std::make_pair(id, EntityContainer()));
	if (pair.second == false)
	{
		std::cout << "[ERROR]: could not insert EntityContainer " << id << " into list\n";
		return false;
	}
	if (pair.first->second.loadContainer(dir) == false)
		return false;
	if (pair.first->second.processContainer(&m_textResource) == false)
		return false;
	return true;
}
