#include "stdafx.h"
#include "Collision.hpp"
#include "sfCollision.hpp"

eeGames::CollisionEngine::CollisionEngine(_COL_TYPE p) : priority(p)
{
}

bool eeGames::CollisionEngine::checkCollision(const Entity & obj1, const Entity & obj2)
{
	// check if both have same collision type
	if (obj1.getCollisionType() == obj2.getCollisionType())
	{
		switch (obj1.getCollisionType())
		{
		case _COL_TYPE::PIXEL:
			return Collision::PixelPerfectTest(obj1.getSprite(), obj2.getSprite());
		case _COL_TYPE::BOX:
			return Collision::BoundingBoxTest(obj1.getSprite(), obj2.getSprite());
		case _COL_TYPE::CIRCLE:
			return Collision::CircleTest(obj1.getSprite(), obj2.getSprite());
		}
	}
	else
	{
		if (obj1.getCollisionType() == _COL_TYPE::PIXEL || obj2.getCollisionType() == _COL_TYPE::PIXEL)
			return Collision::PixelPerfectTest(obj1.getSprite(), obj2.getSprite());
		else
			switch (priority)
			{
			case _COL_TYPE::BOX:
				return Collision::BoundingBoxTest(obj1.getSprite(), obj2.getSprite());
			case _COL_TYPE::CIRCLE:
				return Collision::CircleTest(obj1.getSprite(), obj2.getSprite());
			}
	}

	return false;
}