#pragma once

#include "ee_Entity.hpp"
#include "ee_Animator.hpp"

namespace eeGames
{
	class AnimatedEntity : public Entity
	{
	private:
		Animation _m_sprite;
	public:
		AnimatedEntity()
		{
			m_type = EntityType::ANIMATED;
		}

		bool assignTexture(const sf::Texture *_p_texture, uint32_t _p_width, uint32_t _p_height, uint8_t _p_columns, uint8_t _p_rows)
		{
			if (!_p_texture)
				return false;
			_m_sprite.setSpriteSheet(_p_texture);
			_m_sprite.setFrameSize(_p_width, _p_height);
			_m_sprite.setColumnsRows(_p_columns, _p_rows);
			_m_sprite.createFrames();
			return true;
		}

		void playFrame(uint16_t _p_frameTime);
		void setFrame(uint16_t _p_frame)
		{
			_m_sprite.setCurrentFrame(_p_frame);
		}
	
		virtual void draw(sf::RenderTarget &_p_target, sf::RenderStates _p_state) const
		{
			_p_state.transform *= sf::Transformable::getTransform();
			_p_target.draw(_m_sprite.getCurrentFrame(), _p_state);
		}
	};
}