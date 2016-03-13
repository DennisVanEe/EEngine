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
#include "ee_SoundContainer.hpp"
#include "ee_RenderEngine.hpp"
#include "ee_ResourceEngine.hpp"
#include "ee_KeyedData.hpp"
#include "ee_Algorithms.hpp"

namespace eeGames
{
	enum class CommandType { M_SLEEP, M_WAKE, M_TERM, M_START, D_SAVE, D_LOAD, D_CREATE, D_DESTROY, E_LOAD, E_DESTROY };

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
		SoundContainer *m_soundContainer;
		RequestQueue *m_requestQueue;
		RenderEngine *m_renderEngine;
		ResourceEngine *m_resourceEngine;

		asIScriptEngine *m_engine;
		CScriptBuilder m_scriptBuilder;

		void errorMessageCaller(const asSMessageInfo *msg, void *param);
		void registerEngine();

	public:
		ScriptEngine(DataContainerEngine *_p_dataContainerEngine, RequestQueue *_p_requestQueue, EntityContainerEngine *_p_entityContainerEngine,
			SoundContainer *_p_soundContainer, RenderEngine *_p_renderEngine, ResourceEngine *_p_resourceEngine) : m_dataContainerEngine(_p_dataContainerEngine),
			m_requestQueue(_p_requestQueue), m_entityContainerEngine(_p_entityContainerEngine), m_soundContainer(_p_soundContainer), 
			m_renderEngine(_p_renderEngine), m_resourceEngine(_p_resourceEngine)
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
		bool startModule(const std::string &id, const std::string &dir);
		bool terminateModule(const std::string &id); // will terminate module from memory (and all data)
		bool sleepModule(const std::string &id); // will keep module in memory (and all data), but it won't be executed
		bool wakeModule(const std::string &id);

		bool createDataContainer(const std::string &id);
		bool deleteDataContainer(const std::string &id);
		bool saveDataContainer(const std::string &id, const std::string &dir);
		bool loadDataContainer(const std::string &id, const std::string &dir);

		bool loadEntityContainer(const std::string &id, const std::string &dir);
		bool deleteEntityContainer(const std::string &id);
	};
}