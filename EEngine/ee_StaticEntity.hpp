#pragma once

#include <SFML/Graphics.hpp> 

#include "ee_Entity.hpp"

namespace eeGames
{
	class StaticEntity : public Entity			
	{
	private:
		sf::Sprite _m_sprite;
	public:
		bool assignTexture(const sf::Texture *_p_texture)
		{
			if (!_p_texture)
				return false;
			_m_sprite.setTexture(*_p_texture);
			return false;
		}
		bool assignTexture(const sf::Texture *_p_texture, uint16_t _p_x, uint16_t _p_y, uint16_t _p_width, uint16_t _p_height)
		{
			if (!_p_texture)
				return false;
			_m_sprite.setTexture(*_p_texture);
			_m_sprite.setTextureRect(sf::IntRect(_p_x, _p_y, _p_width, _p_height));
			return false;
		}

		virtual void draw(sf::RenderTarget &_p_target, sf::RenderStates _p_states) const
		{
			_p_states.transform *= sf::Transformable::getTransform();
			_p_target.draw(_m_sprite, _p_states);
		}
	};
}