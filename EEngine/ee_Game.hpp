#pragma once

#include <memory>
#include <SFML/System.hpp>

#include "ee_ScriptEngine.hpp"
#include "ee_DataContainerEngine.hpp"
#include "ee_EntityContainerEngine.hpp"
#include "ee_RenderEngine.hpp"
#include "ee_SoundContainerEngine.hpp"
#include "ee_ScriptInterface.hpp"

namespace eeGames
{
	class Game
	{
	private:
		DataContainerEngine m_dataContainerEngine;
		EntityContainerEngine m_entityContainerEngine;
		SoundContainerEngine m_soundContainerEngine;

		std::unique_ptr<RenderEngine> m_renderEngine;
		std::unique_ptr<ScriptEngine> m_scriptEngine;

	public:
		Game() : m_renderEngine(new RenderEngine(&m_entityContainerEngine)), m_scriptEngine(new ScriptEngine(&m_dataContainerEngine, &m_entityContainerEngine, &m_soundContainerEngine,
			m_renderEngine.get()))
		{
			m_renderEngine->setWindowSettings("Test Window", 1280, 720, false);
			setMouseWindow(m_renderEngine->getWindow());
		}

		void gameLoop()
		{
			m_scriptEngine->startModule("init", "F:/Programming/EE Software Solutions/Example Project/MainLoader.as");
			m_scriptEngine->executeCommands();

			sf::Clock timer;
			while (m_renderEngine->isOpen())
			{
				m_scriptEngine->stepScripts(timer.restart().asMilliseconds());
				m_scriptEngine->executeCommands();
				m_renderEngine->render();
			}
		}
	};
}