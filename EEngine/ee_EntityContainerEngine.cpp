#include "ee_EntityContainerEngine.hpp"

bool eeGames::EntityContainerEngine::load_container(const std::string & dir)
{
	std::string loadScript;

	std::ifstream ifs(dir);
	if (ifs.is_open())
	{
		std::cout << "Loading load script module from file...\n";
		loadScript.assign((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
		ifs.close();

		_module->AddScriptSection("load_module", loadScript.c_str());
		std::cout << "Building load script module...\n";
		_module->Build();

		_context->Prepare(_module->GetFunctionByDecl("void load_main()"));
		int error = _context->Execute();
		if (error != asEXECUTION_FINISHED)
		{
			std::cout << "[ERROR]: Load Module Issue\n";
			return false;
		}
		return true;
	}
	else
	{
		std::cout << "[ERROR]: Could not find or open load file\n";
		return false;
	}
}
