#pragma once

#include "ee_ScriptEngine.hpp"
#include "ee_RenderEngine.hpp"

namespace eeGames
{
	class GameEngine
	{
	private:
		bool _m_gameRunState;
	public:
		void gameLoop();
	};
}