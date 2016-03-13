#include "ee_ScriptEngine.hpp"

// used by the script engine for error handeling
void eeGames::ScriptEngine::errorMessageCaller(const asSMessageInfo *msg, void *param)
{
	std::string type("ERR ");
	if (msg->type == asMSGTYPE_WARNING)
		type = "WARN";
	else if (msg->type == asMSGTYPE_INFORMATION)
		type = "INFO";
	std::cout << msg->section << "(" << msg->row << ", " << msg->col << ") : " << type << " : " << msg->message << std::endl;
}

void eeGames::ScriptEngine::registerEngine()
{
	// set up the error handler:
	m_engine->SetMessageCallback(asMETHOD(ScriptEngine, errorMessageCaller), this, asCALL_THISCALL);
	int error; 

	// register the addons
	RegisterStdString(m_engine);
	RegisterScriptArray(m_engine, true);
	RegisterScriptDictionary(m_engine);
	RegisterScriptMath(m_engine);

	error = m_engine->SetDefaultNamespace("ee"); // the namespace all the following will fall under

	// register the standard functins
	error = m_engine->RegisterGlobalFunction("void consolePrintln(const string &in)", asFUNCTION(consolePrintLine), asCALL_CDECL); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("void consolePrint(const string &in)", asFUNCTION(consolePrint), asCALL_CDECL); assert(error >= 0);

	// writing data to a data container;
	error = m_engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, int8)", asMETHODPR(Request, add_int, (const std::string&, int8_t), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, int16)", asMETHODPR(Request, add_int, (const std::string&, int16_t), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, int32)", asMETHODPR(Request, add_int, (const std::string&, int32_t), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, int64)", asMETHODPR(Request, add_int, (const std::string&, int64_t), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, uint8)", asMETHODPR(Request, add_int, (const std::string&, uint8_t), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, uint16)", asMETHODPR(Request, add_int, (const std::string&, uint16_t), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, uint32)", asMETHODPR(Request, add_int, (const std::string&, uint32_t), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, uint64)", asMETHODPR(Request, add_int, (const std::string&, uint64_t), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, float)", asMETHODPR(Request, add_float, (const std::string&, float), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, double)", asMETHODPR(Request, add_float, (const std::string&, double), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool writeToDataCont(const string &in, const string &in, const string &in)", asMETHOD(Request, add_string), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);

	error = m_engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, int8 &out)", asMETHODPR(Request, get_num, (const std::string&, int8_t*), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, int16 &out)", asMETHODPR(Request, get_num, (const std::string&, int16_t*), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, int32 &out)", asMETHODPR(Request, get_num, (const std::string&, int32_t*), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, int64 &out)", asMETHODPR(Request, get_num, (const std::string&, int64_t*), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, uint8 &out)", asMETHODPR(Request, get_num, (const std::string&, uint8_t*), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, uint16 &out)", asMETHODPR(Request, get_num, (const std::string&, uint16_t*), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, uint32 &out)", asMETHODPR(Request, get_num, (const std::string&, uint32_t*), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, uint64 &out)", asMETHODPR(Request, get_num, (const std::string&, uint64_t*), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, float &out)", asMETHODPR(Request, get_num, (const std::string&, float*), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, double &out)", asMETHODPR(Request, get_num, (const std::string&, double*), bool), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool readFromDataCont(const string &in, const string &in, string &out)", asMETHOD(Request, get_string), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);

	error = m_engine->RegisterGlobalFunction("bool terminateModule(const string &in)", asMETHOD(ScriptEngine, terminateModule), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool startModule(const string &in, const string &in)", asMETHOD(ScriptEngine, startModule), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool sleepModule(const string &in)", asMETHOD(ScriptEngine, sleepModule), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool wakeModule(const string &in)", asMETHOD(ScriptEngine, wakeModule), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);

	error = m_engine->RegisterGlobalFunction("bool createDataConainter(const string &in)", asMETHOD(ScriptEngine, createDataContainer), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool deleteDataContainer(const string &in)", asMETHOD(ScriptEngine, deleteDataContainer), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool saveDataContainer(const string &in, const string &in)", asMETHOD(ScriptEngine, saveDataContainer), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool loadDataContainer(const string &in, const string &in)", asMETHOD(ScriptEngine, loadDataContainer), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);

	error = m_engine->RegisterGlobalFunction("bool loadEntityContainer(const string &in)", asMETHOD(ScriptEngine, loadEntityContainer), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool deleteEntityContainer(const string &in)", asMETHOD(ScriptEngine, deleteEntityContainer), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);

	// register enums for keyboard and mouse presses:
	error = m_engine->RegisterEnum("Mouse"); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Mouse", "Left", 0); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Mouse", "Right", 1); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Mouse", "Middle", 2); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Mouse", "XButton1", 3); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Mouse", "XButton2", 4); assert(error >= 0);

	error = m_engine->RegisterEnum("Key"); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "A", 0); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "B", 1); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "C", 2); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "D", 3); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "E", 4); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "F", 5); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "G", 6); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "H", 7); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "I", 8); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "J", 9); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "K", 10); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "L", 11); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "M", 12); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "N", 13); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "O", 14); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "P", 15); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Q", 16); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "R", 17); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "S", 18); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "T", 19); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "U", 20); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "V", 21); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "W", 22); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "X", 23); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Y", 24); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Z", 25); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Num0", 26); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Num2", 27); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Num3", 28); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Num4", 29); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Num5", 30); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Num6", 31); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Num7", 32); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Num8", 33); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Num9", 34); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Escape", 35); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "LControl", 36); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "LShift", 37); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "LAlt", 38); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "LSystem", 39); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "RControl", 40); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "RShift", 41); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "RAlt", 42); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "RSystem", 43); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Menu", 44); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "LBracket", 45); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "RBracket", 46); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "SemiColon", 47); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Comma", 48); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Period", 49); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Quote", 50); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Slash", 51); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "BackSlash", 52); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Tilde", 53); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Equal", 54); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Dash", 55); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Space", 56); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Return", 57); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "BackSpace", 58); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Tab", 59); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "PageUp", 60); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "PageDown", 61); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "End", 62); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Home", 63); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Insert", 64); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Delete", 65); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Add", 66); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Subtract", 67); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Multiply", 68); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Divide", 69); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Left", 70); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Right", 71); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Up", 72); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Down", 73); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Numpad0", 74); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Numpad1", 75); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Numpad2", 76); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Numpad3", 77); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Numpad4", 78); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Numpad5", 79); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Numpad6", 80); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Numpad7", 81); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Numpad8", 82); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Numpad9", 83); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "F1", 84); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "F2", 85); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "F3", 86); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "F4", 87); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "F5", 88); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "F6", 89); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "F7", 90); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "F8", 91); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "F9", 92); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "F10", 93); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "F11", 94); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "F12", 95); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "F13", 96); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "F14", 97); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "F15", 98); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "Pause", 99); assert(error >= 0);
	error = m_engine->RegisterEnumValue("Key", "KeyCount", 100); assert(error >= 0);

	// register keyboard functions
	error = m_engine->RegisterGlobalFunction("bool iskeyPressed(Key)", asFUNCTION(isKeyPressed), asCALL_CDECL); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("bool isButtonPressed(Mouse)", asFUNCTION(isButtonPressed), asCALL_CDECL); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("int getXPosMouse()", asFUNCTION(getXPosMouse), asCALL_CDECL); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("int getYPosMouse()", asFUNCTION(getYPosMouse), asCALL_CDECL); assert(error >= 0);

	// register AnimatedEntity creation and functions
	error = m_engine->RegisterObjectType("AnimatedEntity", sizeof(AnimatedEntity), asOBJ_VALUE | asOBJ_POD); assert(error >= 0);
	error = m_engine->RegisterObjectBehaviour("AnimatedEntity", asBEHAVE_CONSTRUCT, "void f(const string &in, const string &in)", asMETHOD(RenderEngine, animatedEntityConst), asCALL_THISCALL_OBJLAST, m_renderEngine); assert(error >= 0);
	error = m_engine->RegisterObjectBehaviour("AnimatedEntity", asBEHAVE_DESTRUCT, "void f()", asMETHOD(RenderEngine, animatedEntityDest), asCALL_THISCALL_OBJLAST, m_renderEngine); assert(error >= 0);

	error = m_engine->RegisterObjectMethod("AnimatedEntity", "void playFrame(uint16)", asMETHOD(AnimatedEntity, playFrame), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "void setFrame(uint16)", asMETHOD(AnimatedEntity, setFrame), asCALL_THISCALL); assert(error >= 0);

	// scale and position
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "float getPositionX()", asMETHOD(AnimatedEntity, getPositionX), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "float getPositionY()", asMETHOD(AnimatedEntity, getPositionY), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "float getScaleX()", asMETHOD(AnimatedEntity, getScaleX), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "float getScaleY()", asMETHOD(AnimatedEntity, getScaleY), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "float getOriginX()", asMETHOD(AnimatedEntity, getOriginX), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "float getOriginY()", asMETHOD(AnimatedEntity, getOriginY), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "float getRotation()", asMETHOD(AnimatedEntity, getRotation), asCALL_THISCALL); assert(error >= 0);

	error = m_engine->RegisterObjectMethod("AnimatedEntity", "void setPosition(float, float)", asMETHODPR(AnimatedEntity, setPosition, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "void setScale(float, float)", asMETHODPR(AnimatedEntity, setScale, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "void setOrigin(float, float)", asMETHODPR(AnimatedEntity, setOrigin, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "void setRotation(float)", asMETHOD(AnimatedEntity, setRotation), asCALL_THISCALL); assert(error >= 0);

	error = m_engine->RegisterObjectMethod("AnimatedEntity", "void move(float, float)", asMETHODPR(AnimatedEntity, move, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "void scale(float, float)", asMETHODPR(AnimatedEntity, scale, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "void rotate(float)", asMETHOD(AnimatedEntity, rotate), asCALL_THISCALL); assert(error >= 0);

	// rendering
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "void setRenderLevel(int)", asMETHOD(AnimatedEntity, setRenderLevel), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "int getRenderLevel(int)", asMETHOD(AnimatedEntity, getRenderLevel), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "void setVisible(bool)", asMETHOD(AnimatedEntity, setVisible), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("AnimatedEntity", "bool isVisible()", asMETHOD(AnimatedEntity, isVisible), asCALL_THISCALL); assert(error >= 0);

	// register StaticEntity creation and functions
	error = m_engine->RegisterObjectType("StaticEntity", sizeof(StaticEntity), asOBJ_VALUE | asOBJ_POD); assert(error >= 0);
	error = m_engine->RegisterObjectBehaviour("StaticEntity", asBEHAVE_CONSTRUCT, "void f(const string &in, const string &in)", asMETHOD(RenderEngine, staticEntityConst), asCALL_THISCALL_OBJLAST, m_renderEngine); assert(error >= 0);
	error = m_engine->RegisterObjectBehaviour("StaticEntity", asBEHAVE_DESTRUCT, "void f()", asMETHOD(RenderEngine, staticEntityDest), asCALL_THISCALL_OBJLAST, m_renderEngine); assert(error >= 0);
	
	// scale and position
	error = m_engine->RegisterObjectMethod("StaticEntity", "float getPositionX()", asMETHOD(StaticEntity, getPositionX), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("StaticEntity", "float getPositionY()", asMETHOD(StaticEntity, getPositionY), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("StaticEntity", "float getScaleX()", asMETHOD(StaticEntity, getScaleX), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("StaticEntity", "float getScaleY()", asMETHOD(StaticEntity, getScaleY), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("StaticEntity", "float getOriginX()", asMETHOD(StaticEntity, getOriginX), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("StaticEntity", "float getOriginY()", asMETHOD(StaticEntity, getOriginY), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("StaticEntity", "float getRotation()", asMETHOD(StaticEntity, getRotation), asCALL_THISCALL); assert(error >= 0);

	error = m_engine->RegisterObjectMethod("StaticEntity", "void setPosition(float, float)", asMETHODPR(StaticEntity, setPosition, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("StaticEntity", "void setScale(float, float)", asMETHODPR(StaticEntity, setScale, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("StaticEntity", "void setOrigin(float, float)", asMETHODPR(StaticEntity, setOrigin, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("StaticEntity", "void setRotation(float)", asMETHOD(StaticEntity, setRotation), asCALL_THISCALL); assert(error >= 0);

	error = m_engine->RegisterObjectMethod("StaticEntity", "void move(float, float)", asMETHODPR(StaticEntity, move, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("StaticEntity", "void scale(float, float)", asMETHODPR(StaticEntity, scale, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("StaticEntity", "void rotate(float)", asMETHOD(StaticEntity, rotate), asCALL_THISCALL); assert(error >= 0);

	// rendering
	error = m_engine->RegisterObjectMethod("StaticEntity", "void setRenderLevel(int)", asMETHOD(StaticEntity, setRenderLevel), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("StaticEntity", "int getRenderLevel(int)", asMETHOD(StaticEntity, getRenderLevel), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("StaticEntity", "void setVisible(bool)", asMETHOD(StaticEntity, setVisible), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("StaticEntity", "bool isVisible()", asMETHOD(StaticEntity, isVisible), asCALL_THISCALL); assert(error >= 0);

	// register SoundEffect functions
	error = m_engine->RegisterObjectType("SoundEffect", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("SoundEffect", "void play()", asMETHODPR(SoundEffect, play, (), void), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("SoundEffect", "void play(uint32)", asMETHODPR(SoundEffect, play, (uint32_t), void), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("SoundEffect", "void setLoop(bool)", asMETHOD(SoundEffect, setLoop), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("SoundEffect", "void pause()", asMETHOD(SoundEffect, pause), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("SoundEffect", "void stop()", asMETHOD(SoundEffect, stop), asCALL_THISCALL); assert(error >= 0);

	error = m_engine->RegisterObjectMethod("SoundEffect", "void setPosition(float, float, float)", asMETHOD(SoundEffect, setPosition), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("SoundEffect", "float getPositionX()", asMETHOD(SoundEffect, getPositionX), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("SoundEffect", "float getPositionY()", asMETHOD(SoundEffect, getPositionY), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("SoundEffect", "float getPositionZ()", asMETHOD(SoundEffect, getPositionZ), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("SoundEffect", "bool getLoopStatus()", asMETHOD(SoundEffect, getLoopStatus), asCALL_THISCALL); assert(error >= 0);

	error = m_engine->RegisterObjectMethod("SoundEffect", "void setVolume(uint8)", asMETHOD(SoundEffect, setVolume), asCALL_THISCALL); assert(error >= 0);

	// register Music functions
	error = m_engine->RegisterObjectType("Music", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("Music", "void play()", asMETHODPR(SoundMusic, play, (), void), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("Music", "void play(uint32)", asMETHODPR(SoundMusic, play, (uint32_t), void), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("Music", "void setLoop(bool)", asMETHOD(SoundMusic, setLoop), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("Music", "void pause()", asMETHOD(SoundMusic, pause), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("Music", "void stop()", asMETHOD(SoundMusic, stop), asCALL_THISCALL); assert(error >= 0);

	error = m_engine->RegisterObjectMethod("Music", "void setPosition(float, float, float)", asMETHOD(SoundMusic, setPosition), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("Music", "float getPositionX()", asMETHOD(SoundMusic, getPositionX), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("Music", "float getPositionY()", asMETHOD(SoundMusic, getPositionY), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("Music", "float getPositionZ()", asMETHOD(SoundMusic, getPositionZ), asCALL_THISCALL); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("Music", "bool getLoopStatus()", asMETHOD(SoundMusic, getLoopStatus), asCALL_THISCALL); assert(error >= 0);

	error = m_engine->RegisterObjectMethod("Music", "void setVolume(uint8)", asMETHOD(SoundMusic, setVolume), asCALL_THISCALL); assert(error >= 0);

	// set up music management software
	error = m_engine->RegisterObjectMethod("SoundContainer", "SoundEffect @getSoundEffect(string &in)", asMETHOD(SoundContainer, getSoundEffect), asCALL_THISCALL_ASGLOBAL, m_soundContainer); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("SoundContainer", "SoundEffect @createSoundEffectCopy(string &in, string &in)", asMETHOD(SoundContainer, createSoundEffectCopy), asCALL_THISCALL_ASGLOBAL, m_soundContainer); assert(error >= 0);
	error = m_engine->RegisterObjectMethod("SoundContainer", "Music @getMusic(string &in)", asMETHOD(SoundContainer, getSoundMusic), asCALL_THISCALL_ASGLOBAL, m_soundContainer); assert(error >= 0);

	// register Microphone functions (only one mucrophone, so only one function for controlling it)
	error = m_engine->RegisterGlobalFunction("void setMicrophonePosition(float, float, float)", asFUNCTIONPR(sf::Listener::setPosition, (float, float, float), void), asCALL_CDECL); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("float getMicrophonePositionX()", asFUNCTION(getMicrophonePositionX), asCALL_CDECL); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("float getMicrophonePositionY()", asFUNCTION(getMicrophonePositionY), asCALL_CDECL); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("float getMicrophonePositionZ()", asFUNCTION(getMicrophonePositionZ), asCALL_CDECL); assert(error >= 0);

	error = m_engine->RegisterGlobalFunction("float getMicrophoneVolume()", asFUNCTION(sf::Listener::getGlobalVolume), asCALL_CDECL); assert(error >= 0);
	error = m_engine->RegisterGlobalFunction("void setMicrophoneVolume(float)", asFUNCTION(sf::Listener::setGlobalVolume), asCALL_CDECL); assert(error >= 0);
}

void eeGames::ScriptEngine::initScripts()
{
	for (auto &it : m_currentModuleList)
		it.second->initializeModule();
}

void eeGames::ScriptEngine::stepScripts(uint32_t frameTime)
{
	for (auto &it : m_currentModuleList)
		it.second->stepModule(frameTime);
}

void eeGames::ScriptEngine::executeCommands()
{
	for (auto &it : m_commands)
	{
		switch (it.m_type) // TODO: fix this
		{
		case CommandType::D_DESTROY:
			m_dataContainerEngine->removeContainer(it.m_id);
			break;
		case CommandType::D_CREATE:
			m_dataContainerEngine->addContainer(it.m_id);
			break;
		case CommandType::D_LOAD:
			m_dataContainerEngine->loadContainer(it.m_id, it.m_dir);
			break;
		case CommandType::D_SAVE:
			m_dataContainerEngine->saveContainer(it.m_id, it.m_dir);
			break;
		case CommandType::E_DESTROY:
			m_entityContainerEngine->removeContainer(it.m_id);
			break;
		case CommandType::E_LOAD:
			m_entityContainerEngine->loadContainer(it.m_id, it.m_dir);
			break;
		case CommandType::M_SLEEP:
			m_currentModuleList.find(it.m_id)->second->setSleep(true);
			break;
		case CommandType::M_WAKE:
			m_currentModuleList.find(it.m_id)->second->setSleep(false);
			break;
		case CommandType::M_TERM:
			auto tmp = m_currentModuleList.find(it.m_id);
			tmp->second.release();
			m_currentModuleList.erase(tmp);
			break;
		case CommandType::M_START:
			m_scriptBuilder.StartNewModule(m_engine, it.m_id.c_str());
			int error = m_scriptBuilder.AddSectionFromFile(it.m_dir.c_str());
			if (error < 0) throw std::logic_error("could not find or open file at " + it.m_dir);
			error = m_scriptBuilder.BuildModule();
			if (error < 0) throw std::logic_error("could not build module at " + it.m_dir);
			std::unique_ptr<Module> temp(new Module(m_scriptBuilder.GetModule()));
			temp->initializeModule(); // initialize before running
			m_currentModuleList.insert(std::make_pair(it.m_id, std::move(temp)));
			break;
		default:
			throw std::logic_error("unknown command attempting to be executed");
		}
	}
}

bool eeGames::ScriptEngine::startModule(const std::string &id, const std::string &dir)
{
	if (m_currentModuleList.count(id) != 0)
		return false;

	m_commands.push_back(Command(CommandType::M_START, id, dir));
	return true;
}

bool eeGames::ScriptEngine::terminateModule(const std::string &id)
{
	if (m_currentModuleList.count(id) == 0)
		return false;

	m_commands.push_back(Command(CommandType::M_TERM, id));
	return true;
}

bool eeGames::ScriptEngine::sleepModule(const std::string &id)
{
	if (m_currentModuleList.count(id) == 0)
		return false;

	m_commands.push_back(Command(CommandType::M_SLEEP, id));
	return true;
}

bool eeGames::ScriptEngine::wakeModule(const std::string &id)
{
	if (m_currentModuleList.count(id) == 0)
		return false;

	m_commands.push_back(Command(CommandType::M_WAKE, id));
	return true;
}

bool eeGames::ScriptEngine::createDataContainer(const std::string &id)
{
	if (m_dataContainerEngine->exists(id))
		return false;
	m_commands.push_back(Command(CommandType::D_CREATE, id));
	return true;
}

bool eeGames::ScriptEngine::deleteDataContainer(const std::string &id)
{
	if (m_dataContainerEngine->exists(id) == false)
		return false;
	m_commands.push_back(Command(CommandType::D_DESTROY, id));
	return true;
}

bool eeGames::ScriptEngine::saveDataContainer(const std::string &id, const std::string &dir)
{
	if (m_dataContainerEngine->exists(id) == false)
		return false;
	m_commands.push_back(Command(CommandType::D_SAVE, id, dir));
	return true;
}

bool eeGames::ScriptEngine::loadDataContainer(const std::string &id, const std::string &dir)
{
	if (m_dataContainerEngine->exists(id) == false)
		return false;
	m_commands.push_back(Command(CommandType::D_LOAD, id, dir));
	return true;
}

bool eeGames::ScriptEngine::loadEntityContainer(const std::string &id, const std::string &dir)
{
	if (m_entityContainerEngine->exists(id))
		return false;
	m_commands.push_back(Command(CommandType::E_LOAD, id, dir));
	return true;
}

bool eeGames::ScriptEngine::deleteEntityContainer(const std::string &id)
{
	if (m_entityContainerEngine->exists(id))
		return false;
	m_commands.push_back(Command(CommandType::E_DESTROY, id));
	return true;
}