#include "ee_Module.hpp"

eeGames::Module::Module(const std::string &n, asIScriptEngine *eng) : module_name(n), engine (eng),
	module_loaded(false), suspended(false)
{ 
	module = engine->GetModule(module_name.c_str(), asGM_ALWAYS_CREATE);
	context = engine->CreateContext();
}

eeGames::Module::~Module()
{
	context->Release();
	module->Discard();

	// clear_entities();
}

bool eeGames::Module::is_suspended() const
{
	return suspended;
}

bool eeGames::Module::is_sleep() const
{
	return sleep;
}

void eeGames::Module::set_sleep(bool slp)
{
	sleep = slp;
}

void eeGames::Module::prepare_step()
{
	context->Prepare(module->GetFunctionByDecl(step_decl.c_str()));
}

bool eeGames::Module::load_script(const std::string &dir)
{
	std::ifstream ifs(dir);
	if (ifs.is_open())
	{
		script.assign((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
		ifs.close();

		module->AddScriptSection(module_name.c_str(), script.c_str());
		module->Build();
		module_loaded = true;
		return true;
	}
	else
		return false;
}

const std::string &eeGames::Module::get_module_name() const
{
	return module_name;
}

bool eeGames::Module::initialize_module()
{
	if (!module_loaded)
		return false;

	//context->Prepare(module->GetFunctionByDecl(init_decl.c_str()));
	//context->Execute();

	return true;
}

void eeGames::Module::step_module(asUINT frame_time)
{
	prepare_step();
	if (sleep)
		return;
	context->SetArgDWord(0, frame_time);
	int error = context->Execute();
	if (error != asEXECUTION_FINISHED)
		std::cout << "Module " << module_name << " disrupted from call\n";
}

bool eeGames::Module::resume()
{
	if (!suspended)
		return false;
	context->Execute();
	return true;
}

void eeGames::Module::suspend()
{
	suspended = true; // obviously, it is now in suspension
	context->Suspend();
}

// eeGames::ScriptedEntity &eeGames::Module::create_entity(const std::string &name/*entity stuff*/)
// {
// 	 ScriptedEntity *ent = new ScriptedEntity(); // TODO: add ScriptedEntity constructor parameters
// 	 entities[name] = ent;
// 	 return *ent;
// }

/*
bool eeGames::Module::get_entity(const std::string &name, ScriptedEntity *ent) const
{
	if (!entities.count(name))
		return false;
	ent = entities.find(name)->second;
	return true;
}

bool eeGames::Module::destroy_entity(const std::string &name)
{
	if (!entities.count(name))
		return false;

	ent_list::iterator ent = entities.find(name);
	delete ent->second;
	entities.erase(ent);
	return true;
}

void eeGames::Module::clear_entities()
{
	for (std::pair<std::string, ScriptedEntity*> ent : entities)
		delete ent.second;
}
*/
