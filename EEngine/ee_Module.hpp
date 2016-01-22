#pragma once

#include <angelscript.h>
#include <string>
#include <fstream>
#include <unordered_map>
#include <assert.h>
#include <iostream>

#include "ee_AnimatedEntity.hpp"
#include "ee_StaticEntity.hpp"

// Module holds scripts that can communicate directly with each other
// can create or destroy these scripts

// TODO: make sure sprites are managed in render engine: render engine controls sprite life, script controls position

namespace eeGames
{
	class Module
	{
	private:
		asIScriptModule *_m_module;
		asIScriptContext *_m_context;
		asIScriptEngine *_m_engine;

		void prepareStep(); // might make this public, maybe

		std::string _m_scriptString, _m_moduleName; // TODO: load these values from xml

		// TODO: load these from engine properties xml
		std::string _m_stepDecl = "void step(uint16)";
		std::string _m_initDecl = "void initialize()";

		bool _m_moduleLoaded, _m_moduleInit, _m_sleep, _m_suspended;
	public:
		Module(const std::string &_p_name, asIScriptEngine *_p_engine);
		~Module();

		bool isSuspended() const
		{
			return _m_suspended;
		}
		bool isSleep() const
		{
			return _m_sleep;
		}
		void setSleep(bool _p_sleep)
		{
			_m_sleep = _p_sleep;
		}

		// module modification and loading
		bool loadScript(const std::string &_p_directory);
		const std::string &getModuleName() const
		{
			return _m_moduleName;
		}

		bool initializeModule(); // run only once (so module can prepare for initial run)
		void stepModule(uint16_t _p_frameTime); // run only if module is "awake"
		bool resume(); // should only be used when sleeping

		void suspend();
	};
}
