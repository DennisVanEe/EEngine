#pragma once

#include <unordered_map>
#include <string>
#include <angelscript.h>
#include <scriptstdstring\scriptstdstring.h>
#include <assert.h>
#include <memory>
#include <SFML/System.hpp>

#include "ee_Module.hpp"
#include "ee_RequestQueue.hpp"
#include "ee_DataContainerEngine.hpp"
#include "ee_RequestType.hpp"
#include "ee_EntityContainer.hpp"
#include "ee_ScriptInterface.hpp"
#include "ee_SoundContainer.hpp"

namespace eeGames
{
	extern void MessageCallback(const asSMessageInfo *msg, void *param); // for error handeling

	class ScriptEngine
	{
	private:
		Module *_m_currentActiveModule; // current module that is being executed
		std::unordered_map<std::string, std::unique_ptr<Module>> _m_currentModuleList; // active list of modules

		DataContainerEngine *_m_dataContainerEngine;
		EntityContainer *_m_entityContainer;
		SoundContainer *_m_soundContainer;
		RequestQueue *_m_requestQueue;

		asIScriptEngine *_m_engine;

		void registerEngine();
	public:
		ScriptEngine(DataContainerEngine *_p_dataContainerEngine, RequestQueue *_p_requestQueue) : _m_dataContainerEngine(_p_dataContainerEngine),
			_m_requestQueue(_p_requestQueue)
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
		bool executeRequests();	

		// will act as a global function, even though it is part of this object
		void waitForRequestQueueComp()
		{
			_m_currentActiveModule->suspend();
		} 

		bool startModule(const std::string &_p_name, const std::string &_p_dir);
		bool terminateModule(const std::string &_p_name); // will terminate module from memory (and all data)
		bool sleepModule(const std::string &_p_name); // will keep module in memory (and all data), but it won't be executed
		bool wakeModule(const std::string &_p_name);
	};
}