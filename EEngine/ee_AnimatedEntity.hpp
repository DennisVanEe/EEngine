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
		AnimatedEntity() : Entity() {}

		void assign_texture(sf::Texture *text, uint32_t width, uint32_t height, uint8_t columns, uint8_t rows);

		void play_frame(uint16_t milliseconds);
		void set_frame(uint16_t frame)
		{
			sprite.set_current_frame(frame);
		}
		void draw(uint16_t millisecond, sf::RenderWindow *target)
		{
			sprite.play(millisecond, target);
		}
	};
}