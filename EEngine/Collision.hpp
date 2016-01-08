#pragma once

#include "Entity.hpp"
#include "sfCollision.hpp"

namespace eeGames
{
	class CollisionEngine
	{
	private:
		_COL_TYPE priority;
	public:
		CollisionEngine(_COL_TYPE p); // set the priority (if a circle and square collide, which algorithm is used?) Note: PIXEL collision is always has priority

		void changePriority(_COL_TYPE p)
		{
			priority = p;
		} 

		bool checkCollision(const Entity & obj1, const Entity & obj2);
	};
}
