#include "ee_Module.hpp"

eeGames::Module::Module(const std::string &n, asIScriptEngine *eng) : _m_moduleName(n), _m_engine (eng),
	_m_moduleLoaded(false), _m_suspended(false)
{ 
	_m_module = _m_engine->GetModule(_m_moduleName.c_str(), asGM_ALWAYS_CREATE);
	_m_context = _m_engine->CreateContext();
}

eeGames::Module::~Module()
{
	_m_context->Release();
	_m_module->Discard();
}

void eeGames::Module::prepareStep()
{
	_m_context->Prepare(_m_module->GetFunctionByDecl(_m_stepDecl.c_str()));
}

bool eeGames::Module::loadScript(const std::string &_p_directory)
{
	std::ifstream ifs(_p_directory);
	if (ifs.is_open())
	{
		_m_scriptString.assign((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
		ifs.close();

		_m_module->AddScriptSection(_m_moduleName.c_str(), _m_scriptString.c_str());
		_m_module->Build();
		_m_moduleLoaded = true;
		return true;
	}
	else
		return false;
}

const std::string &eeGames::Module::getModuleName() const
{
	return _m_moduleName;
}

bool eeGames::Module::initializeModule()
{
	if (!_m_moduleLoaded)
		return false;

	_m_context->Prepare(_m_module->GetFunctionByDecl(_m_initDecl.c_str()));
	_m_context->Execute();

	return true;
}

void eeGames::Module::stepModule(uint16_t frame_time)
{
	if (_m_sleep)
		return;
	prepareStep();
	_m_context->SetArgDWord(0, frame_time);
	int error = _m_context->Execute();
	if (error != asEXECUTION_FINISHED)
		std::cout << "Module " << _m_moduleName << " disrupted from call\n";
}

bool eeGames::Module::resume()
{
	if (!_m_suspended)
		return false;
	_m_context->Execute();
	return true;
}

void eeGames::Module::suspend()
{
	_m_suspended = true; // obviously, it is now in suspension
	_m_context->Suspend();
}