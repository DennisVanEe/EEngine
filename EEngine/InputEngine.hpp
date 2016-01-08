#pragma once

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

// allows for mouse and keyboard operations

namespace eeGames
{
	bool keyBoardPress(sf::Keyboard::Key input);
	bool mousePressed(sf::Mouse::Button input);

	const sf::Vector2i & getMousePos();
	int getMousePosX();
	int getMousePosY();

	void setMousePosGlobal(const sf::Vector2i & pos);
	void setMousePosGlobal(int x, int y);

	void setMousePosRelative(const sf::Vector2i & pos);
	void setMousePosRelative(int x, int y);
}
