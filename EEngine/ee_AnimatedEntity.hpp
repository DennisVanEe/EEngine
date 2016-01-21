#pragma once

#include "ee_Entity.hpp"
#include "ee_Animator.hpp"

namespace eeGames
{
	class AnimatedEntity : public Entity
	{
	private:
		Animation sprite;
	public:
		bool assign_texture(const sf::Texture *text, uint32_t width, uint32_t height, uint8_t columns, uint8_t rows)
		{
			if (!text)
				return false;
			sprite.set_sprite_sheet(text);
			sprite.set_frame_size(width, height);
			sprite.set_columns_rows(columns, rows);
			sprite.create_frames();
			return true;
		}

		void play_frame(uint16_t milliseconds);
		void set_frame(uint16_t frame)
		{
			sprite.set_current_frame(frame);
		}
	
		virtual void draw(sf::RenderTarget &target, sf::RenderStates state) const
		{
			state.transform *= sf::Transformable::getTransform();
			target.draw(sprite.get_current_frame(), state);
		}
	};
}