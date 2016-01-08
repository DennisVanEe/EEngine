#pragma once

#include <string>

// SFML API:
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Resource.hpp"

namespace eeGames
{
	// used for collision algorithm (temperaliy using someone else's one)
	// NONE: no collision detetction. Other entities cannot detect its presence
	// CIRCLE: use a circle algorithm to detect collision
	// BOX: create a box and detect collision
	// PIXEL: slowest detection mechanism, is most accurate (pixel perfect)
	enum class _COL_TYPE { NONE, CIRCLE, BOX, PIXEL };

	class Entity
	{
	private:
		const Resource<sf::Texture> & texture; // raw texture resource

		sf::Sprite sprite; // sprite representation of object
		sf::Vector2f origin; //relative origin of the entity;

		// absolute orientation and location
		sf::Vector2f position; //absolute position
		float angle; //current angle in degrees
		int zPosition; //layer location (higher layer number is rendered above others)

		// collision and lighting
		_COL_TYPE collisionType;
		bool blockLight; //whether or not light is blocked 
		bool staticMovement; //whether or not the object can move (used in physics)

		sf::Vector2f previousPosition; // previous position, for collision correction
		float previousAngle; // previous angle, for collision correction

	public:
		Entity(const Resource<sf::Texture> & t, const sf::Vector2f & pos, const sf::Vector2f & org, int zPos, _COL_TYPE type, bool light, bool stat);

		void setPosition(sf::Vector2f pos); // directly change absolute position
		void setAngle(float an); // directly change absolute angle

		void move(sf::Vector2f pos); // relatively move entity
		void rotate(float an); // relatively rotate entity (clockwise)

		// collision
		void setBlockLight(bool light)
		{
			blockLight;
		}
		void setCollisionType(_COL_TYPE type)
		{
			collisionType = type;
		}
		const sf::Vector2f& getPreviousPosition() const
		{
			return previousPosition;
		}
		float getPreviousAngle() const
		{
			return previousAngle;
		}
		const _COL_TYPE getCollisionType() const
		{
			return collisionType;
		}

		// rendering 
		const sf::Sprite & getSprite() const
		{
			return sprite;
		}
		const sf::Vector2f & getOrigin() const
		{
			return origin;
		}
		const sf::Vector2f & getPosition() const
		{
			return position;
		}
		float getAngle() const
		{
			return angle;
		}

		bool operator<(const Entity & ent) const
		{
			return zPosition < ent.zPosition;
		}
		bool operator>(const Entity & ent) const
		{
			return zPosition > ent.zPosition;
		}
	};

	bool lessThanPtrComp(Entity *a, Entity *b);
	bool greaterThanPtrComp(Entity *a, Entity *b);
}

