#pragma once

#include <map>
#include <vector>

#include "ee_Entity.hpp"

namespace eeGames
{
	class RenderEngine
	{
	private:
		std::multimap<uint16_t, Entity*> entities;
		std::vector<sf::View*> views;
		sf::RenderWindow *window;

		uint16_t scale; // number of pixels per coordinate
	public:
		RenderEngine(sf::RenderWindow *window);

		void set_scale(uint16_t sc)
		{
			scale = sc;
		}
		uint16_t get_scale() const
		{
			return scale;
		}

		void add_entity(uint16_t p, Entity *ent)
		{
			render_entities.insert(std::make_pair(p, ent));
		}
		void draw() const;
	};
}