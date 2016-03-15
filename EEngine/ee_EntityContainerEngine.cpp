#include "ee_EntityContainerEngine.hpp"

void eeGames::EntityContainerEngine::loadContainer(const std::string & id, const std::string & dir)
{
	auto pair = m_containers.insert(std::move(std::make_pair(id, EntityContainer())));
	if (pair.second == false)
	{
		std::cout << "Could not insert EntityContainer " << id << " into list\n";
		throw std::runtime_error("could not insert EntityContainer " + id + " into list");
	}
	pair.first->second.loadContainer(dir);
	pair.first->second.processContainer(&m_textResource);
}
