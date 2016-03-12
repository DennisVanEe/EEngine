#include "ee_RenderEngine.hpp"

void eeGames::RenderEngine::render()
{
	m_window.clear();
	for (Entity *currentEnt : renderBuffer)
	{
		if (currentEnt->isVisible())
			m_window.draw(*currentEnt);
	}
	m_window.display();
}
