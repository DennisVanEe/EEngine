#include "ee_SoundContainerEngine.hpp"

float eeGames::getMicrophonePositionX()
{
	return sf::Listener::getPosition().x;
}

float eeGames::getMicrophonePositionY()
{
	return sf::Listener::getPosition().y;
}

float eeGames::getMicrophonePositionZ()
{
	return sf::Listener::getPosition().z;
}