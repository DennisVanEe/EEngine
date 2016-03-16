#include "ee_RenderEngine.hpp"

void eeGames::RenderEngine::render()
{
	if (m_added)
	{
		std::sort(renderBuffer.begin(), renderBuffer.end(), [](Entity *a, Entity *b) {return *a > *b; });
		m_added = false;
	}
	if (m_removed)
	{	
		std::remove_if(renderBuffer.begin(), renderBuffer.end(), [](Entity *a) {return a == nullptr; });
		m_removed = false;
	}

	m_window.pollEvent(m_event);

	if (m_event.type == sf::Event::Closed)
		m_open = false;

	if (m_open == false)
	{
		m_window.close();
		return;
	}

	m_window.clear();
	for (Entity *currentEnt : renderBuffer)
	{
		if (currentEnt->isVisible())
		{
			m_window.draw(*currentEnt);
		}
	}
	m_window.display();
}
