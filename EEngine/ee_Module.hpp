#pragma once

#include <angelscript.h>
#include <string>
#include <fstream>
#include <unordered_map>
#include <assert.h>
#include <vector>

#include "ScriptedEntity.hpp"

// Module holds scripts that can communicate directly with each other
// can create or destroy these scripts

// TODO: make sure sprites are managed in render engine: render engine controls sprite life, script controls position

namespace eeGames
{
	class Module
	{
	protected:
		typedef std::unordered_map<std::string, ScriptedEntity*> ent_list;
	private:
		asIScriptModule *module;
		asIScriptContext *context;
		asIScriptEngine *engine;

		ent_list entities;

		void prepare_step(); // might make this public, maybe

		std::string script, module_name; // TODO: load these values from xml

		// TODO: load these from engine properties xml
		std::string step_decl = "void step(uint)";
		std::string init_decl = "void initialize()";

		bool module_loaded, module_init, sleep, suspended;
	public:
		Module(const std::string &n, asIScriptEngine *eng);
		~Module();

		bool is_suspended() const;
		bool is_sleep() const;
		void set_sleep(bool slp);

		// module modification and loading
		bool load_script(const std::string &dir);
		const std::string &get_module_name() const;

		bool initialize_module(); // run only once (so module can prepare for initial run)
		void step_module(asUINT frame_time); // run only if module is "awake"
		bool resume(); // should only be used when sleeping

		void suspend();

		// ScriptedEntity &create_entity(const std::string &name/*entity stuff*/);
		// bool get_entity(const std::string &name, ScriptedEntity *ent) const;
		// bool destroy_entity(const std::string &name);
		// void clear_entities();
	};
}
