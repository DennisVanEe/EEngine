#include "ee_ScriptEngine.hpp"

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
	_m_engine->SetMessageCallback(asMETHOD(ScriptEngine, errorMessageCaller), this, asCALL_THISCALL);
	int error; 

	// register the standard string
	RegisterStdString(_m_engine);

	// helper functions
	error = _m_engine->RegisterGlobalFunction("void consolePrintLine(const string &in)", asFUNCTION(consolePrintLine), asCALL_CDECL); assert(error >= 0);
	error = _m_engine->RegisterGlobalFunction("void consolePrint(const string &in)", asFUNCTION(consolePrint), asCALL_CDECL); assert(error >= 0);

	// register enums for requests
	error = _m_engine->RegisterEnum("RequestType"); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("RequestType", "WRITE_DATA", 0); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("RequestType", "READ_DATA", 1); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("RequestType", "TERMINATE_MODULE", 2); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("RequestType", "CREATE_MODULE", 3); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("RequestType", "SLEEP_MODULE", 4); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("RequestType", "WAKE_MODULE", 5); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("RequestType", "CREATE_CONTAINER", 6); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("RequestType", "REMOVE_CONTAINER", 7); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("RequestType", "WRITE_CONTAINER_FILE", 8); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("RequestType", "READ_CONTAINER_FILE", 9); assert(error >= 0);

	// register request
	error = _m_engine->RegisterObjectType("Request", 0, asOBJ_REF); assert(error >= 0);
	error = _m_engine->RegisterObjectBehaviour("Request", asBEHAVE_FACTORY, "Request@ f(const string &in, int32, RequestType)", asFUNCTIONPR(create_request, (const std::string&, int32_t, RequestType), Request*), asCALL_CDECL); assert(error >= 0);
	error = _m_engine->RegisterObjectBehaviour("Request", asBEHAVE_FACTORY, "Request@ f(const string &in, const string &in, RequestType)", asFUNCTIONPR(create_request, (const std::string&, const std::string&, RequestType), Request*), asCALL_CDECL); assert(error >= 0);

	error = _m_engine->RegisterObjectBehaviour("Request", asBEHAVE_ADDREF, "void f()", asMETHOD(Request, AddRef), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectBehaviour("Request", asBEHAVE_RELEASE, "void f()", asMETHOD(Request, ReleaseRef), asCALL_THISCALL); assert(error >= 0);

	// register request queue
	error = _m_engine->RegisterObjectType("RequestQueue", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("RequestQueue", "bool add_request(const string &in, Request@)", asMETHOD(RequestQueue, addRequest), asCALL_THISCALL_ASGLOBAL); assert(error >= 0);

	// register ScriptEngine Methods
	error = _m_engine->RegisterObjectMethod("ScriptEngine", "void waitForRequestQueueComp()", asMETHOD(ScriptEngine, waitForRequestQueueComp), asCALL_THISCALL_ASGLOBAL, this); assert(error >= 0);

	// register enums for key presses
	error = _m_engine->RegisterEnum("Button"); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Button", "Left", 0); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Button", "Right", 1); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Button", "Middle", 2); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Button", "XButton1", 3); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Button", "XButton2", 4); assert(error >= 0);

	error = _m_engine->RegisterEnum("Key"); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "A", 0); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "B", 1); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "C", 2); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "D", 3); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "E", 4); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "F", 5); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "G", 6); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "H", 7); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "I", 8); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "J", 9); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "K", 10); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "L", 11); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "M", 12); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "N", 13); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "O", 14); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "P", 15); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Q", 16); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "R", 17); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "S", 18); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "T", 19); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "U", 20); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "V", 21); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "W", 22); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "X", 23); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Y", 24); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Z", 25); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Num0", 26); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Num2", 27); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Num3", 28); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Num4", 29); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Num5", 30); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Num6", 31); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Num7", 32); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Num8", 33); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Num9", 34); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Escape", 35); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "LControl", 36); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "LShift", 37); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "LAlt", 38); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "LSystem", 39); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "RControl", 40); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "RShift", 41); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "RAlt", 42); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "RSystem", 43); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Menu", 44); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "LBracket", 45); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "RBracket", 46); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "SemiColon", 47); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Comma", 48); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Period", 49); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Quote", 50); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Slash", 51); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "BackSlash", 52); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Tilde", 53); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Equal", 54); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Dash", 55); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Space", 56); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Return", 57); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "BackSpace", 58); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Tab", 59); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "PageUp", 60); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "PageDown", 61); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "End", 62); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Home", 63); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Insert", 64); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Delete", 65); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Add", 66); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Subtract", 67); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Multiply", 68); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Divide", 69); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Left", 70); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Right", 71); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Up", 72); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Down", 73); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Numpad0", 74); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Numpad1", 75); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Numpad2", 76); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Numpad3", 77); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Numpad4", 78); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Numpad5", 79); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Numpad6", 80); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Numpad7", 81); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Numpad8", 82); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Numpad9", 83); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "F1", 84); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "F2", 85); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "F3", 86); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "F4", 87); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "F5", 88); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "F6", 89); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "F7", 90); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "F8", 91); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "F9", 92); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "F10", 93); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "F11", 94); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "F12", 95); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "F13", 96); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "F14", 97); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "F15", 98); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "Pause", 99); assert(error >= 0);
	error = _m_engine->RegisterEnumValue("Key", "KeyCount", 100); assert(error >= 0);

	// register keyboard functions
	error = _m_engine->RegisterGlobalFunction("bool iskeyPressed(Key)", asFUNCTION(isKeyPressed), asCALL_CDECL); assert(error >= 0);
	error = _m_engine->RegisterGlobalFunction("bool isButtonPressed(Button)", asFUNCTION(isButtonPressed), asCALL_CDECL); assert(error >= 0);
	error = _m_engine->RegisterGlobalFunction("int getXPosMouse()", asFUNCTION(getXPosMouse), asCALL_CDECL); assert(error >= 0);
	error = _m_engine->RegisterGlobalFunction("int getYPosMouse()", asFUNCTION(getYPosMouse), asCALL_CDECL); assert(error >= 0);

	// register AnimatedEntity creation and functions6
	error = _m_engine->RegisterObjectType("AnimatedEntity", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("AnimatedEntity", "void playFrame(uint16)", asMETHOD(AnimatedEntity, playFrame), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("AnimatedEntity", "void setFrame(uint16)", asMETHOD(AnimatedEntity, setFrame), asCALL_THISCALL); assert(error >= 0);

	// scale and position
	error = _m_engine->RegisterObjectMethod("AnimatedEntity", "float getPositionX()", asMETHOD(AnimatedEntity, getPositionX), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("AnimatedEntity", "float getPositionY()", asMETHOD(AnimatedEntity, getPositionY), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("AnimatedEntity", "float getScaleX()", asMETHOD(AnimatedEntity, getScaleX), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("AnimatedEntity", "float getScaleY()", asMETHOD(AnimatedEntity, getScaleY), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("AnimatedEntity", "float getOriginX()", asMETHOD(AnimatedEntity, getOriginX), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("AnimatedEntity", "float getOriginY()", asMETHOD(AnimatedEntity, getOriginY), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("AnimatedEntity", "float getRotation()", asMETHOD(AnimatedEntity, getRotation), asCALL_THISCALL); assert(error >= 0);

	error = _m_engine->RegisterObjectMethod("AnimatedEntity", "void setPosition(float, float)", asMETHODPR(AnimatedEntity, setPosition, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("AnimatedEntity", "void setScale(float, float)", asMETHODPR(AnimatedEntity, setScale, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("AnimatedEntity", "void setOrigin(float, float)", asMETHODPR(AnimatedEntity, setOrigin, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("AnimatedEntity", "void setRotation(float)", asMETHOD(AnimatedEntity, setRotation), asCALL_THISCALL); assert(error >= 0);

	error = _m_engine->RegisterObjectMethod("AnimatedEntity", "void move(float, float)", asMETHODPR(AnimatedEntity, move, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("AnimatedEntity", "void scale(float, float)", asMETHODPR(AnimatedEntity, scale, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("AnimatedEntity", "void rotate(float)", asMETHOD(AnimatedEntity, rotate), asCALL_THISCALL); assert(error >= 0);

	// register StaticEntity creation and functions
	error = _m_engine->RegisterObjectType("StaticEntity", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(error >= 0);

	// scale and position
	error = _m_engine->RegisterObjectMethod("StaticEntity", "float getPositionX()", asMETHOD(StaticEntity, getPositionX), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("StaticEntity", "float getPositionY()", asMETHOD(StaticEntity, getPositionY), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("StaticEntity", "float getScaleX()", asMETHOD(StaticEntity, getScaleX), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("StaticEntity", "float getScaleY()", asMETHOD(StaticEntity, getScaleY), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("StaticEntity", "float getOriginX()", asMETHOD(StaticEntity, getOriginX), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("StaticEntity", "float getOriginY()", asMETHOD(StaticEntity, getOriginY), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("StaticEntity", "float getRotation()", asMETHOD(StaticEntity, getRotation), asCALL_THISCALL); assert(error >= 0);

	error = _m_engine->RegisterObjectMethod("StaticEntity", "void setPosition(float, float)", asMETHODPR(StaticEntity, setPosition, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("StaticEntity", "void setScale(float, float)", asMETHODPR(StaticEntity, setScale, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("StaticEntity", "void setOrigin(float, float)", asMETHODPR(StaticEntity, setOrigin, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("StaticEntity", "void setPosition(float, float)", asMETHODPR(StaticEntity, setPosition, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("StaticEntity", "void setRotation(float)", asMETHOD(StaticEntity, setRotation), asCALL_THISCALL); assert(error >= 0);

	error = _m_engine->RegisterObjectMethod("StaticEntity", "void move(float, float)", asMETHODPR(StaticEntity, move, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("StaticEntity", "void scale(float, float)", asMETHODPR(StaticEntity, scale, (float, float), void), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("StaticEntity", "void rotate(float)", asMETHOD(StaticEntity, rotate), asCALL_THISCALL); assert(error >= 0);

	// set up entity management software
	error = _m_engine->RegisterObjectMethod("EntityContainer", "AnimatedEntity @getAnimatedEntity(string &in)", asMETHOD(EntityContainer, getAnimatedEntity), asCALL_THISCALL_ASGLOBAL, _m_soundContainer); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("EntityContainer", "StaticEntity @getStaticEntity(string &in)", asMETHOD(EntityContainer, getStaticEntity), asCALL_THISCALL_ASGLOBAL, _m_soundContainer); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("EntityContainer", "AnimatedEntity @createAnimatedEntityCopy(string &in, string &in)", asMETHOD(EntityContainer, createAnimatedEntityCopy), asCALL_THISCALL_ASGLOBAL, _m_soundContainer); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("EntityContainer", "StaticEntity @createStaticEntityCopy(string &in, string &in)", asMETHOD(EntityContainer, createStaticEntityCopy), asCALL_THISCALL_ASGLOBAL, _m_soundContainer); assert(error >= 0);

	// adding stuff to the render engine
	error = _m_engine->RegisterObjectMethod("RenderEngine", "void addEntityToRender(uint16, AnimatedEntity@, string &in)", asMETHOD(RenderEngine, addEntity), asCALL_THISCALL_ASGLOBAL, _m_renderEngine); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("RenderEngine", "void addEntityToRender(uint16, StaticEntity@, string &in)", asMETHOD(RenderEngine, addEntity), asCALL_THISCALL_ASGLOBAL, _m_renderEngine); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("RenderEngine", "bool removeEntityToRender(string &in)", asMETHOD(RenderEngine, removeEntity), asCALL_THISCALL_ASGLOBAL, _m_renderEngine); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("RenderEngine", "void clearAllEntityToRender()", asMETHOD(RenderEngine, clearAllEntities), asCALL_THISCALL_ASGLOBAL, _m_renderEngine); assert(error >= 0);

	// register SoundEffect functions
	error = _m_engine->RegisterObjectType("SoundEffect", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("SoundEffect", "void play()", asMETHODPR(SoundEffect, play, (), void), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("SoundEffect", "void play(uint32)", asMETHODPR(SoundEffect, play, (uint32_t), void), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("SoundEffect", "void setLoop(bool)", asMETHOD(SoundEffect, setLoop), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("SoundEffect", "void pause()", asMETHOD(SoundEffect, pause), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("SoundEffect", "void stop()", asMETHOD(SoundEffect, stop), asCALL_THISCALL); assert(error >= 0);

	error = _m_engine->RegisterObjectMethod("SoundEffect", "void setPosition(float, float, float)", asMETHOD(SoundEffect, setPosition), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("SoundEffect", "float getPositionX()", asMETHOD(SoundEffect, getPositionX), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("SoundEffect", "float getPositionY()", asMETHOD(SoundEffect, getPositionY), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("SoundEffect", "float getPositionZ()", asMETHOD(SoundEffect, getPositionZ), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("SoundEffect", "uint32 getPositionZ()", asMETHOD(SoundEffect, getPlayPosition), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("SoundEffect", "bool getLoopStatus()", asMETHOD(SoundEffect, getLoopStatus), asCALL_THISCALL); assert(error >= 0);

	error = _m_engine->RegisterObjectMethod("SoundEffect", "void setVolume(uint8)", asMETHOD(SoundEffect, setVolume), asCALL_THISCALL); assert(error >= 0);

	// register Music functions
	error = _m_engine->RegisterObjectType("Music", 0, asOBJ_REF | asOBJ_NOCOUNT); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("Music", "void play()", asMETHODPR(SoundMusic, play, (), void), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("Music", "void play(uint32)", asMETHODPR(SoundMusic, play, (uint32_t), void), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("Music", "void setLoop(bool)", asMETHOD(SoundMusic, setLoop), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("Music", "void pause()", asMETHOD(SoundMusic, pause), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("Music", "void stop()", asMETHOD(SoundMusic, stop), asCALL_THISCALL); assert(error >= 0);

	error = _m_engine->RegisterObjectMethod("Music", "void setPosition(float, float, float)", asMETHOD(SoundMusic, setPosition), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("Music", "float getPositionX()", asMETHOD(SoundMusic, getPositionX), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("Music", "float getPositionY()", asMETHOD(SoundMusic, getPositionY), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("Music", "float getPositionZ()", asMETHOD(SoundMusic, getPositionZ), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("Music", "uint32 getPositionZ()", asMETHOD(SoundMusic, getPlayPosition), asCALL_THISCALL); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("Music", "bool getLoopStatus()", asMETHOD(SoundMusic, getLoopStatus), asCALL_THISCALL); assert(error >= 0);

	error = _m_engine->RegisterObjectMethod("SoundEffect", "void setVolume(uint8)", asMETHOD(SoundMusic, setVolume), asCALL_THISCALL); assert(error >= 0);

	// set up music management software
	error = _m_engine->RegisterObjectMethod("SoundContainer", "SoundEffect @getSoundEffect(string &in)", asMETHOD(SoundContainer, getSoundEffect), asCALL_THISCALL_ASGLOBAL, _m_soundContainer); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("SoundContainer", "SoundEffect @createSoundEffectCopy(string &in, string &in)", asMETHOD(SoundContainer, createSoundEffectCopy), asCALL_THISCALL_ASGLOBAL, _m_soundContainer); assert(error >= 0);
	error = _m_engine->RegisterObjectMethod("SoundContainer", "Music @getMusic(string &in)", asMETHOD(SoundContainer, getSoundMusic), asCALL_THISCALL_ASGLOBAL, _m_soundContainer); assert(error >= 0);

	// register Microphone functions
	error = _m_engine->RegisterGlobalFunction("void setMicrophonePosition(float, float, float)", asFUNCTIONPR(sf::Listener::setPosition, (float, float, float), void), asCALL_CDECL); assert(error >= 0);
	error = _m_engine->RegisterGlobalFunction("float getMicrophonePositionX()", asFUNCTION(getMicrophonePositionX), asCALL_CDECL); assert(error >= 0);
	error = _m_engine->RegisterGlobalFunction("float getMicrophonePositionY()", asFUNCTION(getMicrophonePositionY), asCALL_CDECL); assert(error >= 0);
	error = _m_engine->RegisterGlobalFunction("float getMicrophonePositionZ()", asFUNCTION(getMicrophonePositionZ), asCALL_CDECL); assert(error >= 0);

	error = _m_engine->RegisterGlobalFunction("float getMicrophoneVolume()", asFUNCTION(sf::Listener::getGlobalVolume), asCALL_CDECL); assert(error >= 0);
	error = _m_engine->RegisterGlobalFunction("void setMicrophoneVolume(float)", asFUNCTION(sf::Listener::setGlobalVolume), asCALL_CDECL); assert(error >= 0);
}

bool eeGames::ScriptEngine::executeScripts(uint16_t _p_frame_time)
{
	for (auto &module : _m_currentModuleList)
	{
		_m_currentActiveModule = module.second.get();
		module.second->stepModule(_p_frame_time);
	}

	_m_requestQueue->finalizeRequests();
	executeRequests();

	for (auto &module : _m_currentModuleList)
	{
		if (module.second->isSuspended())
			module.second->resume();
	}

	return true;
}

bool eeGames::ScriptEngine::executeRequests()
{
	bool exitSuccess = true;
	auto *reqQueue = _m_requestQueue->getQueue();

	for (auto req : *reqQueue)
	{
		switch (req.second.first->getRequest())
		{
		case RequestType::WRITE_DATA:
			_m_dataContainerEngine->addData(req.second.second, req.second.first->getDataType(), req.second.first->getTargetName(), req.second.first->getData());
			break;
		case RequestType::READ_DATA:
			req.second.first->addData(_m_dataContainerEngine->getData(req.second.second, req.second.first->getTargetName()));
			break;
		case RequestType::TERMINATE_MODULE:
			terminateModule(req.second.second);
			break;
		case RequestType::CREATE_MODULE:
			startModule(req.second.second, req.second.first->getTargetName());
			break;
		case RequestType::SLEEP_MODULE:
			sleepModule(req.second.second);
			break;
		case RequestType::WAKE_MODULE:
			wakeModule(req.second.second);
			break;
		case RequestType::CREATE_CONTAINER:
			_m_dataContainerEngine->addContainer(req.second.second);
			break;
		case RequestType::REMOVE_CONTAINER:
			_m_dataContainerEngine->removeContainer(req.second.second);
			break;
		case RequestType::WRITE_CONTAINER_FILE:
			_m_dataContainerEngine->saveContainer(req.second.second, req.second.first->getTargetName());
			break;
		case RequestType::READ_CONTAINER_FILE:
			_m_dataContainerEngine->loadContainer(req.second.second, req.second.first->getTargetName());
			break;
		default:
			exitSuccess = false;
			break;
		}
		req.second.first->AddRef();
	}
	_m_requestQueue->clearQueue();
	return exitSuccess;
}

bool eeGames::ScriptEngine::startModule(const std::string &_p_name, const std::string &_p_dir)
{
	std::unique_ptr<Module> mod_ptr(new Module(_p_name, _m_engine));
	if (!mod_ptr->loadScript(_p_dir))
		return false;
	mod_ptr->initializeModule();
	_m_currentModuleList.insert(std::make_pair(_p_name, std::move(mod_ptr)));
	return true;
}

bool eeGames::ScriptEngine::terminateModule(const std::string &_p_name)
{
	auto it = _m_currentModuleList.find(_p_name);
	if (it == _m_currentModuleList.end())
		return false;

	it->second.release();
	_m_currentModuleList.erase(it);
	return true;
}

bool eeGames::ScriptEngine::sleepModule(const std::string &_p_name)
{
	auto it = _m_currentModuleList.find(_p_name);
	if (it == _m_currentModuleList.end())
		return false;

	it->second->setSleep(true);
	return true;
}

bool eeGames::ScriptEngine::wakeModule(const std::string &_p_name)
{
	auto it = _m_currentModuleList.find(_p_name);
	if (it == _m_currentModuleList.end())
		return false;

	it->second->setSleep(false);
	return true;
}