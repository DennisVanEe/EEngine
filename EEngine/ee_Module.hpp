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
		asIScriptModule *m_module;
		asIScriptContext *m_context;
		asIScriptEngine *m_engine;

		// TODO: load these from engine properties xml
		std::string _m_stepDecl = "void step(int)";
		std::string _m_initDecl = "void initialize()";

		bool m_sleep;

	public:
		Module(asIScriptModule *mod); // module initialized by module builder addon
		~Module();

		bool isSleep() const
		{
			return m_sleep;
		}
		void setSleep(bool _p_sleep)
		{
			m_sleep = _p_sleep;
		}

		bool bindFunctions()
		{
			switch (m_module->BindAllImportedFunctions())
			{
			case asERROR:
			case asCANT_BIND_ALL_FUNCTIONS:
				return false;
			default:
				return true;
			}
		}

		// module modification and loading
		std::string getModuleName() const
		{
			return std::move(std::string(m_module->GetName()));
		}

		bool initializeModule(); // run only once (so module can prepare for initial run)
		void stepModule(uint32_t frameTime); // run only if module is "awake"
	};
}
