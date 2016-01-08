#include "Window.hpp"

eeGames::Window::Window(sf::Vector2u res, const std::string & tit, bool fullscrn, bool vsync) : title(tit), isClosed(false)
{
	create(res, tit, fullscrn, vsync);
}

eeGames::Window::Window()
{
}

void eeGames::Window::setResolution(sf::Vector2u res)
{
	sf::RenderWindow::setSize(res);
}

void eeGames::Window::create(sf::Vector2u res, const std::string & title, bool fullscrn, bool vsync)
{
	if (fullscrn)
		sf::RenderWindow::create(sf::VideoMode(res.x, res.y), title, sf::Style::Fullscreen);
	else
		sf::RenderWindow::create(sf::VideoMode(res.x, res.y), title, sf::Style::Default);
	sf::RenderWindow::setVerticalSyncEnabled(vsync);
}

void eeGames::Window::setFullScreen(bool fullscrn)
{
	if (fullscrn)
		sf::RenderWindow::create(sf::VideoMode(sf::RenderWindow::getSize().x, sf::RenderWindow::getSize().y), 
			title, sf::Style::Fullscreen);
	else
		sf::RenderWindow::create(sf::VideoMode(sf::RenderWindow::getSize().x, sf::RenderWindow::getSize().y), 
			title, sf::Style::Default);
}
