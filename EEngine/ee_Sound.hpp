#pragma once

#include <SFML/Audio.hpp>

namespace eeGames
{
	class Sound
	{
	public:
		virtual void play() = 0;
		virtual void play(uint32_t _p_startTime) = 0;
		virtual void pause() = 0;
		virtual void stop() = 0;

		virtual void setPosition(float _p_x, float _p_y, float _p_z) = 0;
		virtual void setVolume(uint8_t _p_volume) = 0;
	};
}
