#pragma once

#include <SFML/Audio.hpp>

namespace eeGames
{
	class Sound
	{
	public:
		virtual void play() = 0;
		virtual void play(uint32_t _p_startTime) = 0;
		virtual void setLoop(bool) = 0;
		virtual void pause() = 0;
		virtual void stop() = 0;

		virtual void setPosition(float _p_x, float _p_y, float _p_z) = 0;
		virtual float getPositionX() const = 0;
		virtual float getPositionY() const = 0;
		virtual float getPositionZ() const = 0;
		virtual uint32_t getPlayPosition() const = 0;
		virtual bool getLoopStatus() const = 0;

		virtual void setVolume(uint8_t _p_volume) = 0;
	};
}
