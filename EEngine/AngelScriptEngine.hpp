#pragma once

#include <angelscript.h>
#include <scriptstdstring\scriptstdstring.h>

#include <assert.h>

#include "ScriptedEntity.hpp"
#include "InputEngine.hpp"
#include "Level.hpp"

namespace eeGames
{
	class AngelScriptEngine
	{
	private:
		void createScriptEngine();
		void registerEngineParts();
		asIScriptEngine *engine; // the AngelScript engine that will handle the scripts
		asIScriptFunction *step_function;

		std::string superScript; // combination of all scripts in level
		std::string moduleName;
		bool scriptLoaded, scriptCompiled, engineCreated;
	public:
		AngelScriptEngine() : scriptLoaded(false), scriptCompiled(false), engineCreated(false)
		{
			createScriptEngine();
		}

		void loadLevelScript(Level & level);
		void compileScript();
		bool executeScript(double frame_time);
	};
}