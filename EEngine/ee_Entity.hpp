#pragma once

#include <SFML/Graphics.hpp>

namespace eeGames
{
	class Entity : public sf::Transformable, public sf::Drawable
	{
	public:
		float getPositionX() const
		{
			return getPosition().x;
		}
		float getPositionY() const
		{
			return getPosition().y;
		}
		float getScaleX() const
		{
			return getScale().x;
		}
		float getScaleY() const
		{
			return getScale().y;
		}
		float getOriginX() const
		{
			return getOrigin().x;
		}
		float getOriginY() const
		{
			return getOrigin().y;
		}
	};
}
