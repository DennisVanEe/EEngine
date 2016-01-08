#pragma once

// EEngine
#include "Level.hpp"
#include "Collision.hpp"
#include "AngelScriptEngine.hpp"
#include "eeContainer.hpp"
#include "Window.hpp"

namespace eeGames
{
	class RenderEngine
	{
	private:
		//LightEngine lightEngine;
		//CollisionEngine collisionEngine;
		//AngelScriptEngine & scriptEngine;

		Level *level;
		Window *renderWindow;

	public:
		RenderEngine();

		void setWindow(Window & rt);
		void setLevel(Level & lev);

		inline void step(double frame_time)
		{
			level->step(frame_time);

			std::vector<Entity*> Entities = level->getRenderEntities();

			renderWindow->clear();

			for (Entity* ent : Entities)
				renderWindow->draw(ent->getSprite());

			renderWindow->display();
		}
	};
}