#include "InputEngine.hpp"

bool eeGames::keyBoardPress(sf::Keyboard::Key input)
{
	return sf::Keyboard::isKeyPressed(input);
}

bool eeGames::mousePressed(sf::Mouse::Button input)
{
	return sf::Mouse::isButtonPressed(input);
}

const sf::Vector2i & eeGames::getMousePos()
{
	return sf::Mouse::getPosition();
}

int eeGames::getMousePosX()
{
	return getMousePos().x;
}

int eeGames::getMousePosY()
{
	return getMousePos().y;
}

void eeGames::setMousePosGlobal(const sf::Vector2i & pos)
{
	// TODO: pass window
}

void eeGames::setMousePosGlobal(int x, int y)
{
	// TODO: pass window
}

void eeGames::setMousePosRelative(const sf::Vector2i & pos)
{
	sf::Mouse::setPosition(pos);
}

void eeGames::setMousePosRelative(int x, int y)
{
	sf::Mouse::setPosition(sf::Vector2i(x, y));
}

