#pragma once

#include <string>
#include <angelscript.h>
#include <assert.h>
#include <memory>
#include <SFML/System.hpp>
#include <stdint.h> 

// AngelScript Addons
#include <scriptstdstring\scriptstdstring.h>
#include <scriptarray\scriptarray.h>
#include <scriptmath\scriptmath.h> // no complex numbers for now
#include <scriptbuilder\scriptbuilder.h>
#include <scriptdictionary\scriptdictionary.h>

#include "ee_Module.hpp"
#include "ee_RequestQueue.hpp"
#include "ee_DataContainerEngine.hpp"
#include "ee_RequestType.hpp"
#include "ee_EntityContainer.hpp"
#include "ee_ScriptInterface.hpp"
#include "ee_RenderEngine.hpp"
#include "ee_ResourceEngine.hpp"
#include "ee_KeyedData.hpp"
#include "ee_Algorithms.hpp"
#include "ee_SoundContainerEngine.hpp"

namespace eeGames
{
	enum class CommandType { M_SLEEP, M_WAKE, M_TERM, M_START, D_SAVE, D_LOAD, D_CREATE, D_DESTROY, E_LOAD, E_DESTROY, SE_LOAD, SE_DESTROY, SM_LOAD, SM_DESTROY };

	class ScriptEngine
	{
	private:
		KeyedData<std::string, std::unique_ptr<Module>> m_currentModuleList; // active list of modules

		// commands for scripts:
		struct Command
		{
			CommandType m_type;
			std::string m_id, m_dir;
			Command(CommandType type, std::string id, std::string dir = "") : m_type(type), m_id(id), m_dir(dir) {}
		};
		std::vector <Command> m_commands;
	
		DataContainerEngine *m_dataContainerEngine;
		EntityContainerEngine *m_entityContainerEngine;
		SoundContainerEngine *m_soundContainerEngine;
		RenderEngine *m_renderEngine;

		asIScriptEngine *m_engine;
		CScriptBuilder m_scriptBuilder;

		void errorMessageCaller(const asSMessageInfo *msg, void *param);
		void registerEngine();

	public:
		ScriptEngine(DataContainerEngine *dataContainerEngine, EntityContainerEngine *entityContainerEngine,
			SoundContainerEngine *soundContainerEngine, RenderEngine *renderEngine) : m_dataContainerEngine(dataContainerEngine),
			m_entityContainerEngine(entityContainerEngine), m_soundContainerEngine(soundContainerEngine), m_renderEngine(renderEngine) 
		{
			m_engine = asCreateScriptEngine();
			registerEngine();
		}
		~ScriptEngine()
		{
			m_engine->ShutDownAndRelease();
		}

		ScriptEngine(const ScriptEngine &) = delete;
		ScriptEngine &operator=(const ScriptEngine &) = delete;

		void initScripts();
		void stepScripts(uint32_t frameTime);
		void executeCommands();

		// used by the scripts for engine communication:
		void startModule(const std::string &id, const std::string &dir)
		{
			m_commands.push_back(Command(CommandType::M_START, id, dir));
		}
		void terminateModule(const std::string &id)
		{
			m_commands.push_back(Command(CommandType::M_TERM, id));
		}
		void sleepModule(const std::string &id)
		{
			m_commands.push_back(Command(CommandType::M_SLEEP, id));
		}
		void wakeModule(const std::string &id)
		{
			m_commands.push_back(Command(CommandType::M_WAKE, id));
		}

		void createDataContainer(const std::string &id)
		{
			m_commands.push_back(Command(CommandType::D_CREATE, id));
		}
		void deleteDataContainer(const std::string &id)
		{
			m_commands.push_back(Command(CommandType::D_DESTROY, id));
		}
		void saveDataContainer(const std::string &id, const std::string &dir)
		{
			m_commands.push_back(Command(CommandType::D_SAVE, id, dir));
		}
		void loadDataContainer(const std::string &id, const std::string &dir)
		{
			m_commands.push_back(Command(CommandType::D_LOAD, id, dir));
		}

		void loadEntityContainer(const std::string &id, const std::string &dir)
		{
			m_commands.push_back(Command(CommandType::E_LOAD, id, dir));
		}
		void deleteEntityContainer(const std::string &id)
		{
			m_commands.push_back(Command(CommandType::E_DESTROY, id));
		}

		void loadSoundContainer(const std::string &id, const std::string &dir)
		{
			m_commands.push_back(Command(CommandType::SE_LOAD, id, dir));
		}
		void loadMusicContainer(const std::string &id, const std::string &dir)
		{
			m_commands.push_back(Command(CommandType::SM_LOAD, id, dir));
		}
		void removeSoundContainer(const std::string &id)
		{
			m_commands.push_back(Command(CommandType::SE_DESTROY, id));
		}
		void removeMusicContainer(const std::string &id)
		{
			m_commands.push_back(Command(CommandType::SM_DESTROY, id));
		}
	};
}