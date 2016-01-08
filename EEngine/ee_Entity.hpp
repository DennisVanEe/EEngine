#pragma once

#include <SFML/Graphics.hpp>

namespace eeGames
{
	class Entity : public sf::Transformable
	{
	protected:
		sf::Texture *texture; // points to the texture in the resource container
		sf::RenderWindow *render_window;
	public:
		Entity(sf::RenderWindow *rend_wid) : Transformable(), render_window(rend_wid) {}

		virtual void assign_texture(sf::Texture *text) = 0;
		virtual void draw(unsigned int millisecond) = 0;
	};
}
