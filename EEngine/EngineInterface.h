#pragma once

#include "EExceptionHandler.hpp"
#include "Project.hpp"

#include <string>
#include <assert.h>
#include <iostream>
#include <tinyxml2.h>

namespace eeGames
{
	class EngineInterface
	{
	private:
		tinyxml2::XMLDocument projectFile;

	public:	
		bool loadProject(const std::string & XMLDIR);
		void executeProject();
	};
}
