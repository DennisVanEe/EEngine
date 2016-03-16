#pragma once

#include "ee_Entity.hpp"
#include "ee_Animator.hpp"

namespace eeGames
{
	class AnimatedEntity : public Entity
	{
	private:
		Animation m_sprite;
	public:
		AnimatedEntity()
		{
			renderLev = 0;
			render = true;
			m_type = EntityType::ANIMATED;
		}

		bool assignTexture(const sf::Texture *texture, uint32_t columns, uint32_t rows, uint32_t frameNum)
		{
			if (m_sprite.setSpriteSheet(texture, columns, rows, frameNum) == false)
				return false;
			if (m_sprite.createFrames() == false)
				return false;
			return true;
		}

		void playFrame(uint32_t frameTime)
		{
			m_sprite.play(frameTime);
		}
		void setFrame(uint32_t frame)
		{
			m_sprite.setCurrentFrame(frame);
		}
		void setFrameTime(uint32_t time)
		{
			m_sprite.setFrameTime(time);
		}
	
		virtual void draw(sf::RenderTarget &_p_target, sf::RenderStates _p_state) const
		{
			_p_state.transform *= sf::Transformable::getTransform();
			_p_target.draw(m_sprite.getCurrentFrame(), _p_state);
		}
	};
}