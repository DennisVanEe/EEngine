#pragma once

#include <SFML/Graphics.hpp> 

#include "ee_Entity.hpp"

namespace eeGames
{
	class StaticEntity : public Entity			
	{
	private:
		sf::Sprite sprite;
	public:
		bool assign_texture(const sf::Texture *text)
		{
			if (!text)
				return false;
			sprite.setTexture(*text);
			return false;
		}
		bool assign_texture(const sf::Texture *text, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
		{
			if (!text)
				return false;
			sprite.setTexture(*text);
			sprite.setTextureRect(sf::IntRect(x, y, width, height));
			return false;
		}

		virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const
		{
			state.transform *= sf::Transformable::getTransform();
			target.draw(sprite, state); 
		}
	};
}