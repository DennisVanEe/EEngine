#pragma once

#include <SFML/Graphics.hpp>

namespace eeGames
{
	class Entity : public sf::Transformable
	{
	protected:
		sf::Texture *texture; // points to the texture in the resource container
	public:
		Entity() : Transformable() {}

		virtual void draw(uint16_t millisecond, sf::RenderWindow *target) = 0;
	};
}
