#include "ee_ScriptEngine.hpp"

void eeGames::MessageCallback(const asSMessageInfo *msg, void *param)
{
	const char *type = "ERR ";
	if (msg->type == asMSGTYPE_WARNING)
		type = "WARN";
	else if (msg->type == asMSGTYPE_INFORMATION)
		type = "INFO";
	printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

bool eeGames::ScriptEngine::execute_scripts(uint16_t frame_time)
{
	for (auto &module : current_module_list)
	{
		current_active_module = module.second.get();
		module.second->step_module(frame_time);
	}

	request_queue.finalize_requests();
	execute_requests();

	for (auto &module : current_module_list)
	{
		if (module.second->is_suspended())
			module.second->resume();
	}

	return true;
}

bool eeGames::ScriptEngine::execute_requests()
{
	bool success = true;
	auto *req_queue = request_queue.get_queue();

	for (auto req : *req_queue)
	{
		switch (req.second.first->get_request())
		{
		case RequestType::WRITE_DATA:
			data_container.add_data(req.second.second, req.second.first->get_data_type(), req.second.first->get_target_name(), req.second.first->get_data());
			break;
		case RequestType::READ_DATA:
			req.second.first->add_data(data_container.get_data(req.second.second, req.second.first->get_target_name()));
			break;
		case RequestType::TERMINATE_MODULE:
			terminate_module(req.second.second);
			break;
		case RequestType::CREATE_MODULE:
			start_module(req.second.second, req.second.first->get_target_name());
			break;
		case RequestType::SLEEP_MODULE:
			sleep_module(req.second.second);
			break;
		case RequestType::WAKE_MODULE:
			wake_module(req.second.second);
			break;
		case RequestType::CREATE_CONTAINER:
			data_container.add_container(req.second.second);
			break;
		case RequestType::REMOVE_CONTAINER:
			data_container.remove_container(req.second.second);
			break;
		case RequestType::WRITE_CONTAINER_FILE:
			data_container.save_container(req.second.second, req.second.first->get_target_name());
			break;
		case RequestType::READ_CONTAINER_FILE:
			data_container.load_container(req.second.second, req.second.first->get_target_name());
			break;
		default:
			success = false;
			break;
		}
		req.second.first->AddRef();
	}
	request_queue.clear_queue();
	return success;
}

void eeGames::ScriptEngine::register_engine()
{
	engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL);

	int error; // used for error checking

	// register the standard string
	RegisterStdString(engine);

	// helper functions
	error = engine->RegisterGlobalFunction("void consolePrintLine(const string &in)", asFUNCTION(consolePrintLine), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("void consolePrint(const string &in)", asFUNCTION(consolePrint), asCALL_CDECL); assert(error >= 0);

	// register enums for requests
	error = engine->RegisterEnum("RequestType"); assert(error >= 0);
	error = engine->RegisterEnumValue("RequestType", "WRITE_DATA", 0); assert(error >= 0);
	error = engine->RegisterEnumValue("RequestType", "READ_DATA", 1); assert(error >= 0);
	error = engine->RegisterEnumValue("RequestType", "TERMINATE_MODULE", 2); assert(error >= 0);
	error = engine->RegisterEnumValue("RequestType", "CREATE_MODULE", 3); assert(error >= 0);
	error = engine->RegisterEnumValue("RequestType", "SLEEP_MODULE", 4); assert(error >= 0);
	error = engine->RegisterEnumValue("RequestType", "WAKE_MODULE", 5); assert(error >= 0);
	error = engine->RegisterEnumValue("RequestType", "CREATE_CONTAINER", 6); assert(error >= 0);
	error = engine->RegisterEnumValue("RequestType", "REMOVE_CONTAINER", 7); assert(error >= 0);
	error = engine->RegisterEnumValue("RequestType", "WRITE_CONTAINER_FILE", 8); assert(error >= 0);
	error = engine->RegisterEnumValue("RequestType", "READ_CONTAINER_FILE", 9); assert(error >= 0);

	// register request
	error = engine->RegisterObjectType("Request", 0, asOBJ_REF); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Request", asBEHAVE_FACTORY, "Request@ f(const string &in, uint16, RequestType)", asFUNCTIONPR(create_request, (const std::string&, uint16_t, RequestType), Request*), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Request", asBEHAVE_FACTORY, "Request@ f(const string &in, uint16, RequestType, const string &in)", asFUNCTIONPR(create_request, (const std::string&, uint16_t, RequestType, const std::string&), Request*), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Request", asBEHAVE_FACTORY, "Request@ f(const string &in, uint16, RequestType, const string &in, int &in)", asFUNCTIONPR(create_request, (const std::string&, uint16_t, RequestType, const std::string&, int*), Request*), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Request", asBEHAVE_FACTORY, "Request@ f(const string &in, uint16, RequestType, const string &in, float &in)", asFUNCTIONPR(create_request, (const std::string&, uint16_t, RequestType, const std::string&, float*), Request*), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Request", asBEHAVE_FACTORY, "Request@ f(const string &in, uint16, RequestType, const string &in, double &in)", asFUNCTIONPR(create_request, (const std::string&, uint16_t, RequestType, const std::string&, double*), Request*), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Request", asBEHAVE_FACTORY, "Request@ f(const string &in, uint16, RequestType, const string &in, bool &in)", asFUNCTIONPR(create_request, (const std::string&, uint16_t, RequestType, const std::string&, bool*), Request*), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Request", asBEHAVE_FACTORY, "Request@ f(const string &in, uint16, RequestType, const string &in, string &in)", asFUNCTIONPR(create_request, (const std::string&, uint16_t, RequestType, const std::string&, std::string&), Request*), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Request", asBEHAVE_FACTORY, "Request@ f(const string &in, const string &in, RequestType)", asFUNCTIONPR(create_request, (const std::string&, const std::string&, RequestType), Request*), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Request", asBEHAVE_FACTORY, "Request@ f(const string &in, const string &in, RequestType, const string &in)", asFUNCTIONPR(create_request, (const std::string&, const std::string&, RequestType, const std::string&), Request*), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Request", asBEHAVE_FACTORY, "Request@ f(const string &in, const string &in, RequestType, const string &in, int &in)", asFUNCTIONPR(create_request, (const std::string&, const std::string&, RequestType, const std::string&, int*), Request*), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Request", asBEHAVE_FACTORY, "Request@ f(const string &in, const string &in, RequestType, const string &in, float &in)", asFUNCTIONPR(create_request, (const std::string&, const std::string&, RequestType, const std::string&, float*), Request*), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Request", asBEHAVE_FACTORY, "Request@ f(const string &in, const string &in, RequestType, const string &in, double &in)", asFUNCTIONPR(create_request, (const std::string&, const std::string&, RequestType, const std::string&, double*), Request*), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Request", asBEHAVE_FACTORY, "Request@ f(const string &in, const string &in, RequestType, const string &in, bool &in)", asFUNCTIONPR(create_request, (const std::string&, const std::string&, RequestType, const std::string&, bool*), Request*), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Request", asBEHAVE_FACTORY, "Request@ f(const string &in, const string &in, RequestType, const string &in, string &in)", asFUNCTIONPR(create_request, (const std::string&, const std::string&, RequestType, const std::string&, std::string&), Request*), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Request", asBEHAVE_ADDREF, "void f()", asMETHOD(Request, AddRef), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Request", asBEHAVE_RELEASE, "void f()", asMETHOD(Request, ReleaseRef), asCALL_THISCALL); assert(error >= 0);

	error = engine->RegisterObjectMethod("Request", "int get_int(bool &out)", asMETHODPR(Request, get_int, (bool*), int), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Request", "int get_int()", asMETHODPR(Request, get_int, (), int), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Request", "float get_float(bool &out)", asMETHODPR(Request, get_float, (bool*), float), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Request", "float get_float()", asMETHODPR(Request, get_float, (), float), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Request", "double get_double(bool &out)", asMETHODPR(Request, get_double, (bool*), double), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Request", "double get_double()", asMETHODPR(Request, get_double, (), double), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Request", "bool get_bool(bool &out)", asMETHODPR(Request, get_bool, (bool*), bool), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Request", "bool get_bool()", asMETHODPR(Request, get_bool, (bool*), bool), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Request", "string get_string(bool &out)", asMETHODPR(Request, get_string, (bool*), std::string), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Request", "string get_string()", asMETHODPR(Request, get_string, (), std::string), asCALL_THISCALL); assert(error >= 0);

	// register request queue
	error = engine->RegisterObjectType("RequestQueue", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(error >= 0);
	error = engine->RegisterObjectMethod("RequestQueue", "bool add_request(const string &in, Request@)", asMETHOD(RequestQueue, add_request), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterGlobalProperty("RequestQueue requestQueue", &request_queue); assert(error >= 0);

	// register ScriptEngine Methods
	error = engine->RegisterObjectMethod("ScriptEngine", "void waitForRequestQueueComp()", asMETHOD(ScriptEngine, waitForRequestQueueComp), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);

	// register enums for key presses
	error = engine->RegisterEnum("Button"); assert(error >= 0);
	error = engine->RegisterEnumValue("Button", "Left", 0); assert(error >= 0);
	error = engine->RegisterEnumValue("Button", "Right", 1); assert(error >= 0);

	error = engine->RegisterEnum("Key"); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "A", 0); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "B", 1); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "C", 2); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "D", 3); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "E", 4); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F", 5); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "G", 6); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "H", 7); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "I", 8); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "J", 9); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "K", 10); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "L", 11); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "M", 12); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "N", 13); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "O", 14); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "P", 15); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Q", 16); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "R", 17); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "S", 18); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "T", 19); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "U", 20); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "V", 21); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "W", 22); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "X", 23); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Y", 24); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Z", 25); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num0", 26); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num2", 27); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num3", 28); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num4", 29); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num5", 30); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num6", 31); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num7", 32); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num8", 33); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Num9", 34); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Escape", 35); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "LControl", 36); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "LShift", 37); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "LAlt", 38); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "LSystem", 39); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "RControl", 40); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "RShift", 41); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "RAlt", 42); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "RSystem", 43); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Menu", 44); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "LBracket", 45); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "RBracket", 46); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "SemiColon", 47); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Comma", 48); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Period", 49); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Quote", 50); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Slash", 51); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "BackSlash", 52); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Tilde", 53); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Equal", 54); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Dash", 55); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Space", 56); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Return", 57); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "BackSpace", 58); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Tab", 59); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "PageUp", 60); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "PageDown", 61); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "End", 62); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Home", 63); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Insert", 64); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Delete", 65); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Add", 66); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Subtract", 67); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Multiply", 68); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Divide", 69); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Left", 70); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Right", 71); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Up", 72); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Down", 73); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad0", 74); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad1", 75); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad2", 76); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad3", 77); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad4", 78); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad5", 79); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad6", 80); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad7", 81); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad8", 82); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Numpad9", 83); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F1", 84); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F2", 85); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F3", 86); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F4", 87); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F5", 88); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F6", 89); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F7", 90); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F8", 91); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F9", 92); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F10", 93); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F11", 94); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F12", 95); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F13", 96); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F14", 97); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "F15", 98); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "Pause", 99); assert(error >= 0);
	error = engine->RegisterEnumValue("Key", "KeyCount", 100); assert(error >= 0);

	error = engine->RegisterGlobalFunction("bool iskeyPressed(Key)", asFUNCTION(isKeyPressed), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool isButtonPressed(Button)", asFUNCTION(isButtonPressed), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("int getXPosMouse()", asFUNCTION(getXPosMouse), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("int getYPosMouse()", asFUNCTION(getYPosMouse), asCALL_CDECL); assert(error >= 0);
}

bool eeGames::ScriptEngine::start_module(const std::string &name, const std::string &dir)
{
	std::unique_ptr<Module> mod_ptr(new Module(name, engine));
	if (!mod_ptr->load_script(dir))
		return false;
	mod_ptr->initialize_module();
	current_module_list.insert(std::make_pair(name, std::move(mod_ptr)));
	return true;
}

bool eeGames::ScriptEngine::terminate_module(const std::string &name)
{
	auto it = current_module_list.find(name);
	if (it == current_module_list.end())
		return false;

	it->second.release();
	current_module_list.erase(it);
	return true;
}

bool eeGames::ScriptEngine::sleep_module(const std::string &name)
{
	auto it = current_module_list.find(name);
	if (it == current_module_list.end())
		return false;

	it->second->set_sleep(true);
	return true;
}

bool eeGames::ScriptEngine::wake_module(const std::string &name)
{
	auto it = current_module_list.find(name);
	if (it == current_module_list.end())
		return false;

	it->second->set_sleep(false);
	return true;
}