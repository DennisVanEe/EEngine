#include "stdafx.h"

#include <iostream>

#include "Entity.hpp"

// Entity methods:

eeGames::Entity::Entity(const Resource<sf::Texture> & t, const sf::Vector2f & pos, const sf::Vector2f & org, int zPos, _COL_TYPE type, bool light, bool stat)
	: texture(t), position(pos), zPosition(zPos), sprite(), origin(org), collisionType(type), blockLight(light), staticMovement(stat)
{
	// setup the sprite
	sprite.setTexture(texture.getTexture());
	sprite.setPosition(position);
	sprite.setOrigin(origin);

	// collision setup:
	previousPosition = getPosition();
	previousAngle = getAngle();
}

void eeGames::Entity::setPosition(sf::Vector2f pos)
{
	previousPosition = position;
	position = pos;
	sprite.setPosition(position);
}
void eeGames::Entity::setAngle(float an)
{
	previousAngle = angle;
	angle = an;
	sprite.setRotation(angle);
}

void eeGames::Entity::move(sf::Vector2f pos)
{
	previousPosition = position;
	position += pos;
	sprite.move(pos);
}
void eeGames::Entity::rotate(float an)
{
	previousAngle = angle;
	angle += an;
	sprite.rotate(an);
}

bool eeGames::lessThanPtrComp(eeGames::Entity *a, eeGames::Entity *b)
{
	return *a < *b;
}
bool eeGames::greaterThanPtrComp(eeGames::Entity *a, eeGames::Entity *b)
{
	return *a > *b;
}

