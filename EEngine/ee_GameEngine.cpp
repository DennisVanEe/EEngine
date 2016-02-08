#include "ee_GameEngine.hpp"

void eeGames::GameEngine::gameLoop()
{
	sf::Clock time;

	// load game elements
	while (gameRunning)
	{
		_m_ScriptEngine->executeScripts(time.restart().asMilliseconds());
		_m_renderEngine->render();
	}
}
