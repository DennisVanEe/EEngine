#include "ee_Module.hpp"

eeGames::Module::Module(asIScriptModule *mod) : m_module(mod)
{ 
	m_engine = m_module->GetEngine();
	m_context = m_engine->CreateContext();
}

eeGames::Module::~Module()
{
	m_context->Release();
	m_module->Discard();
}

bool eeGames::Module::initializeModule()
{
	m_context->Prepare(m_module->GetFunctionByDecl(_m_initDecl.c_str()));
	m_context->Execute();

	return true;
}

void eeGames::Module::stepModule(uint32_t frameTime)
{
	if (m_sleep)
		return;

	m_context->Prepare(m_module->GetFunctionByDecl(_m_stepDecl.c_str()));
	m_context->SetArgDWord(0, frameTime);
	int error = m_context->Execute();
}