#pragma once

#include <map>

#include "ee_Entity.hpp"

namespace eeGames
{
	class RenderEngine
	{
	private:
		std::multimap<uint16_t, Entity*> entities; //current entities being rendered
		std::vector<sf::View*> views;
		sf::RenderWindow *window;

	public:
		RenderEngine(sf::RenderWindow *window);

		uint16_t get_scale() const
		{
			return scale;
		}

		void add_entity(uint16_t p, Entity *ent)
		{
			entities.insert(std::make_pair(p, ent));
		}
		void draw(uint16_t frame_time) const;
	};
}