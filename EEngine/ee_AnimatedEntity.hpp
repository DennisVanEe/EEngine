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
		AnimatedEntity(sf::RenderWindow *rend_wid) : Entity(rend_wid), sprite(rend_wid) {}

		void assign_texture(sf::Texture *text);

		void play_frame(unsigned int milliseconds);
		void set_frame(unsigned int frame);
		void restart_frame();
	};
}