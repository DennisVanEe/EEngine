#pragma once

// standard
#include <string>
// SFML
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
// EEngine

namespace eeGames
{
	class Window : public sf::RenderWindow
	{
	private:
		// no way to get title from window object:
		std::string title;
		bool isClosed;
	public:
		Window();
		Window(sf::Vector2u res, const std::string & title, bool fullscrn, bool vsync);

		// chaning window:
		void create(sf::Vector2u res, const std::string & title, bool fullscrn, bool vsync);
		void setResolution(sf::Vector2u res);
		void setFullScreen(bool fullscrn);
	};
}