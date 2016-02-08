#pragma once

#include <memory>

#include "ee_ScriptEngine.hpp"

namespace eeGames
{
	class GameEngine
	{
	private:
		bool gameRunning;
	private:
		std::unique_ptr<DataContainerEngine> _m_dataContainerEngine;
		std::unique_ptr<EntityContainer> _m_entityContainer;
		std::unique_ptr<SoundContainer> _m_soundContainer;
		std::unique_ptr<RequestQueue> _m_requestQueue;
		std::unique_ptr<RenderEngine> _m_renderEngine;
		std::unique_ptr<ScriptEngine> _m_ScriptEngine;
	public:
		GameEngine() : _m_dataContainerEngine(new DataContainerEngine()), _m_entityContainer(new EntityContainer()),
			_m_soundContainer(new SoundContainer()), _m_requestQueue(new RequestQueue()), _m_renderEngine(new RenderEngine()),
			_m_ScriptEngine(new ScriptEngine(_m_dataContainerEngine.get(), _m_requestQueue.get(), _m_entityContainer.get(),
				_m_soundContainer.get(), _m_renderEngine.get()))
		{
		}

		void playIntoScene();
		void gameLoop();
	};
}
