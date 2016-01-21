#pragma once

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
