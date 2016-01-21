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
#include "ee_ScriptInterface.hpp"

namespace eeGames
{
	extern void MessageCallback(const asSMessageInfo *msg, void *param); // for error handeling

	class ScriptEngine
	{
	protected:
		typedef std::unordered_map<std::string, std::unique_ptr<Module>> mod_list;
	private:
		Module *current_active_module; // current module that is being executed
		mod_list current_module_list; // active list of modules
		DataContainerEngine data_container;
		RequestQueue request_queue;

		asIScriptEngine *engine;

		void register_engine();
	public:
		ScriptEngine()
		{
			engine = asCreateScriptEngine();
			register_engine();
		}
		ScriptEngine(const ScriptEngine &) = delete;
		ScriptEngine &operator=(const ScriptEngine &) = delete;

		bool execute_scripts(uint16_t frame_time);

		bool execute_requests();	

		// will act as a global function, even though it is part of this object
		void waitForRequestQueueComp()
		{
			current_active_module->suspend();
		} 

		bool start_module(const std::string &name, const std::string &dir);
		bool terminate_module(const std::string &name); // will terminate module from memory (and all data)
		bool sleep_module(const std::string &name); // will keep module in memory (and all data), but it won't be executed
		bool wake_module(const std::string &name);
	};
}