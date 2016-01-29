#pragma once

// EEngine Copyright (c) 2016
// ee_ScriptInterface.hpp
// --------------------------------------------------------
// An interface that holds function definitions for basic 
// functions that a user can use these functions do not 
// belong in any other specific class or part of the Engine

#include <SFML\Graphics.hpp>
#include <iostream>

namespace eeGames
{
	extern inline bool isKeyPressed(sf::Keyboard::Key key);
	extern inline bool isButtonPressed(sf::Mouse::Button button);
	extern inline int getXPosMouse();
	extern inline int getYPosMouse();
	extern void consolePrintLine(const std::string &input);
	extern void consolePrint(const std::string &input);
}
