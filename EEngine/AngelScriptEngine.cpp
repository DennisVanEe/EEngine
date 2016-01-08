#include "stdafx.h"
#include "AngelScriptEngine.hpp"

// TODO: add in register file
std::string stepFunction = "void step(double)";

// An example MessageCallBack for debugging
void MessageCallback(const asSMessageInfo *msg, void *param)
{
	const char *type = "ERR ";
	if (msg->type == asMSGTYPE_WARNING)
		type = "WARN";
	else if (msg->type == asMSGTYPE_INFORMATION)
		type = "INFO";
	printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}

void eeGames::AngelScriptEngine::registerEngineParts()
{
	int error;

	RegisterStdString(engine);

	// Register ScriptedEntity methods:
	error = engine->RegisterObjectType("Entity", 0, asOBJ_REF); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Entity", asBEHAVE_ADDREF, "void f()", asMETHOD(ScriptedEntity, AddRef), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("Entity", asBEHAVE_RELEASE, "void f()", asMETHOD(ScriptedEntity, ReleaseRef), asCALL_THISCALL); assert(error >= 0);

	error = engine->RegisterObjectMethod("Entity", "void setPosition(float, float)", asMETHOD(ScriptedEntity, setPosition, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Entity", "void move(float, float)", asMETHOD(ScriptedEntity, move, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Entity", "float getPreviousPositionX()", asMETHOD(ScriptedEntity, getPreviousPositionX), asCALL_THISCALL); assert(error >= 0); 
	error = engine->RegisterObjectMethod("Entity", "float getPreviousPositionY()", asMETHOD(ScriptedEntity, getPreviousPositionY), asCALL_THISCALL); assert(error >= 0); 
	error = engine->RegisterObjectMethod("Entity", "float getPositionX()", asMETHOD(ScriptedEntity, getPositionX), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Entity", "float getPositionY()", asMETHOD(ScriptedEntity, getPositionY), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Entity", "void setAngle(float an)", asMETHOD(ScriptedEntity, setAngle), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Entity", "void rotate(float an)", asMETHOD(ScriptedEntity, rotate), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Entity", "void setBlockLight(bool light)", asMETHOD(ScriptedEntity, setBlockLight), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Entity", "float getAngle()", asMETHOD(ScriptedEntity, getAngle), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectMethod("Entity", "float getPreviousAngle()", asMETHOD(ScriptedEntity, getPreviousAngle), asCALL_THISCALL); assert(error >= 0);

	// Register eeContainer of scripted entities:

	error = engine->RegisterObjectType("eeContainer<ScriptedEntity>", 0, asOBJ_REF | asOBJ_TEMPLATE); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("eeContainer<ScriptedEntity>", asBEHAVE_ADDREF, "void f()", asMETHOD(eeContainer<ScriptedEntity>, AddRef), asCALL_THISCALL); assert(error >= 0);
	error = engine->RegisterObjectBehaviour("eeContainer<ScriptedEntity>", asBEHAVE_RELEASE, "void f()", asMETHOD(eeContainer<ScriptedEntity>, ReleaseRef), asCALL_THISCALL); assert(error >= 0);

	error = engine->RegisterObjectMethod("eeContainer<ScriptedEntity>", "Entity& getObject(string)", asMETHOD(eeContainer<ScriptedEntity>, getObject), asCALL_THISCALL); assert(error >= 0);

	// Register InputEngine functions:

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

	error = engine->RegisterGlobalFunction("bool keyBoardPress(Key)", asFUNCTION(keyBoardPress), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("bool mousePressed(Button)", asFUNCTION(mousePressed), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("int getMousePosX()", asFUNCTION(getMousePosX), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("int getMousePosY()", asFUNCTION(getMousePosY), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("void setMousePosGlobal(int, int)", asFUNCTIONPR(setMousePosGlobal, (int, int), void), asCALL_CDECL); assert(error >= 0);
	error = engine->RegisterGlobalFunction("void setMousePosRelative(int, int)", asFUNCTIONPR(setMousePosRelative, (int, int), void), asCALL_CDECL); assert(error >= 0);
}

void eeGames::AngelScriptEngine::createScriptEngine()
{
	engine = asCreateScriptEngine();
	
	// for call back erros (will work on this in the future)
	int error = engine->SetMessageCallback(asFUNCTION(MessageCallback), 0, asCALL_CDECL); assert(error >= 0);
	registerEngineParts();

	engineCreated = true;
}

void eeGames::AngelScriptEngine::loadLevelScript(Level & level)
{
	assert(engineCreated);

	const eeContainer<ScriptedEntity>& tmpEnt = level.getConstScriptedEntities();
	const std::vector<std::string>& tmpNames = tmpEnt.getNameList();

	// attaches all of the scripts
	for (std::string name : tmpNames)
	{
		superScript += tmpEnt.getConstObject(name).getScript();
	}

	superScript += level.getStepScript();

	int error = engine->RegisterGlobalProperty("eeContainer<ScriptedEntity> entityList", &level.getScriptedEntities()); assert(error >= 0);

	scriptLoaded = true;
	moduleName = level.getModuleName();
}

void eeGames::AngelScriptEngine::compileScript()
{
	assert(scriptLoaded);

	// TODO: Method for naming modules
	asIScriptModule *module = engine->GetModule(moduleName.c_str(), asGM_ALWAYS_CREATE);
	module->AddScriptSection(moduleName.c_str(), superScript.c_str());

	int error = module->Build(); assert(error >= 0);

	step_function = module->GetFunctionByDecl(stepFunction.c_str()); assert(step_function != nullptr);

	scriptCompiled = true;
}

bool eeGames::AngelScriptEngine::executeScript(double frame_time)
{
	assert(scriptCompiled);

	asIScriptContext *ctx = engine->CreateContext();

	int error = ctx->Prepare(step_function); assert(error >= 0);

	error = ctx->SetArgDouble(0, frame_time); assert(error >= 0);

	error = ctx->Execute(); assert(error >= 0);
	ctx->Release();

	return true;
}