#pragma once

#include <SFML/Graphics.hpp> 

#include "ee_Entity.hpp"

namespace eeGames
{
	class StaticEntity : public Entity			
	{
	private:
		sf::Sprite m_sprite;
	public:
		StaticEntity()
		{
			m_type = EntityType::STATIC;
		}

		bool assignTexture(const sf::Texture *texture)
		{
			if (!texture)
				return false;
			m_sprite.setTexture(*texture);
			return false;
		}
		bool assignTexture(const sf::Texture *texture, uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			if (!texture)
				return false;
			m_sprite.setTexture(*texture);
			m_sprite.setTextureRect(sf::IntRect(x, y, width, height));
			return true;
		}

		virtual void draw(sf::RenderTarget &_p_target, sf::RenderStates _p_states) const
		{
			_p_states.transform *= sf::Transformable::getTransform();
			_p_target.draw(m_sprite, _p_states);
		}
	};
}