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

namespace eeGames
{
	enum class CommandType {M_SLEEP, M_WAKE, M_TERM, M_START, D_SAVE, D_LOAD, D_CREATE, D_DESTROY};

	class ScriptEngine
	{
	private:
		KeyedData<std::string, std::unique_ptr<Module>> _m_currentModuleList; // active list of modules

		// commands:
		std::vector <std::pair<CommandType, Module*>> m_commands;
	
		DataContainerEngine *_m_dataContainerEngine;
		EntityContainerEngine *_m_entityContainerEngine;
		SoundContainer *_m_soundContainer;
		RequestQueue *_m_requestQueue;
		RenderEngine *_m_renderEngine;
		ResourceEngine *_m_resourceEngine;

		asIScriptEngine *_m_engine;
		CScriptBuilder m_scriptBuilder;

		void errorMessageCaller(const asSMessageInfo *msg, void *param);
		void registerEngine();
		std::string dirParser(const std::string &dir);

	public:
		ScriptEngine(DataContainerEngine *_p_dataContainerEngine, RequestQueue *_p_requestQueue, EntityContainerEngine *_p_entityContainerEngine,
			SoundContainer *_p_soundContainer, RenderEngine *_p_renderEngine, ResourceEngine *_p_resourceEngine) : _m_dataContainerEngine(_p_dataContainerEngine),
			_m_requestQueue(_p_requestQueue), _m_entityContainerEngine(_p_entityContainerEngine), _m_soundContainer(_p_soundContainer), 
			_m_renderEngine(_p_renderEngine), _m_resourceEngine(_p_resourceEngine)
		{
			_m_engine = asCreateScriptEngine();
			registerEngine();
		}
		~ScriptEngine()
		{
			_m_engine->ShutDownAndRelease();
		}

		ScriptEngine(const ScriptEngine &) = delete;
		ScriptEngine &operator=(const ScriptEngine &) = delete;

		bool executeScripts(uint16_t _p_frameTime);
		bool executeCommands();

		// used by the scripts for engine communication:
		bool startModule(const std::string &_p_name, const std::string &_p_dir)
		{
			std::unique_ptr<Module> mod_ptr(new Module(_p_name, _m_engine));
			if (!mod_ptr->loadScript(_p_dir))
				return false;
			mod_ptr->initializeModule();
			_m_currentModuleList.insert(std::make_pair(_p_name, std::move(mod_ptr)));
			return true;
		}
		bool terminateModule(const std::string &id); // will terminate module from memory (and all data)
		bool sleepModule(const std::string &_p_name); // will keep module in memory (and all data), but it won't be executed
		bool wakeModule(const std::string &_p_name);

		bool createDataContainer(const std::string &id);
		bool deleteDataContainer(const std::string &id);
		bool saveDataContainer(const std::string &id, const std::string &dir);
		bool loadDataContainer(const std::string &id, const std::string &dir);

		bool loadEntityContainer(const std::string &dir);
		bool deleteEntityContainer(const std::string &id);
	};
}