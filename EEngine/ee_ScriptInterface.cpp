#include "ee_ScriptInterface.hpp"

inline bool eeGames::isKeyPressed(sf::Keyboard::Key k)
{
	return sf::Keyboard::isKeyPressed(k);
}

inline bool eeGames::isButtonPressed(sf::Mouse::Button b)
{
	return sf::Mouse::isButtonPressed(b);
}

inline int eeGames::getXPosMouse()
{
	return sf::Mouse::getPosition().x;
}

inline int eeGames::getYPosMouse()
{
	return sf::Mouse::getPosition().y;
}

void eeGames::consolePrintLine(const std::string &input)
{
	std::cout << input << std::endl;
}

void eeGames::consolePrint(const std::string &input)
{
	std::cout << input;
}