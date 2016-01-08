#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <angelscript.h>
#include <scriptstdstring\scriptstdstring.h>
#include <assert.h>
#include <Windows.h> // for windows compatibility
#include <SFML/System.hpp>

#include "ee_Module.hpp"
#include "ee_RequestQueue.hpp"
#include "ee_DataContainerEngine.hpp"
#include "ee_RequestType.hpp"

namespace eeGames
{
	class ScriptEngine
	{
	protected:
		typedef std::unordered_map<std::string, Module*> mod_list;
	private:
		Module *current_active_module; // current module that is being executed
		mod_list module_list; // active list of modules
		DataContainerEngine data_container;
		RequestQueue request_queue;

		asIScriptEngine *engine;

		void register_engine();
	public:
		ScriptEngine();
		~ScriptEngine();

		bool execute_scripts(float frame_time);

		// resource management
		bool execute_requests();	
		void waitForRequestQueueComp();

		bool start_module(const std::string &name, const std::string &dir);
		bool terminate_module(const std::string &name); // will terminate module from memory (and all data)
		bool sleep_module(const std::string &name); // will keep module in memory (and all data), but it won't be executed
		bool wake_module(const std::string &name);
	};

	// script functions 
	extern inline bool isKeyPressed(sf::Keyboard::Key key);
	extern inline bool isButtonPressed(sf::Mouse::Button button);
	extern inline int getXPosMouse();
	extern inline int getYPosMouse();
	extern void consolePrintLine(const std::string &input);
	extern void consolePrint(const std::string &input);
	extern void MessageCallback(const asSMessageInfo *msg, void *param);
}