#pragma once

// standard
#include <string>
// EEngine
#include "LoadingEngine.hpp"
#include "AngelScriptEngine.hpp"
#include "RenderEngine.hpp"
#include "Window.hpp"

namespace eeGames
{
	class Project
	{
	private:
		tinyxml2::XMLDocument projectFile;

		LoadingEngine loadEngine;
		eeContainer<Level> & levels; // for easier access
		RenderEngine renderEngine;
		Window window;

	public:
		bool load(const std::string & PXML);
		void executeLevel(const std::string & levName);
	};
}
