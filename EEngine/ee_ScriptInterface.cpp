#include "ee_ScriptInterface.hpp"

sf::RenderWindow *mouseWindow;

inline bool eeGames::isKeyPressed(sf::Keyboard::Key k)
{
	return sf::Keyboard::isKeyPressed(k);
}

inline bool eeGames::isButtonPressed(sf::Mouse::Button b)
{
	return sf::Mouse::isButtonPressed(b);
}

inline void eeGames::setMouseWindow(sf::RenderWindow *window)
{
	mouseWindow = window;
}

inline int eeGames::getXPosMouse()
{
	return sf::Mouse::getPosition(*mouseWindow).x;
}

inline int eeGames::getYPosMouse()
{
	return sf::Mouse::getPosition(*mouseWindow).y;
}

void eeGames::consolePrintLine(const std::string &input)
{
	std::cout << input << std::endl;
}

void eeGames::consolePrint(const std::string &input)
{
	std::cout << input;
}