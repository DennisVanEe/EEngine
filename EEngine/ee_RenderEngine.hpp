#pragma once

#include <map>

#include "ee_Entity.hpp"

namespace eeGames
{
	class RenderEngine
	{
	private:
		std::multimap<unsigned int, Entity*> render_entities;
	public:

	};
}