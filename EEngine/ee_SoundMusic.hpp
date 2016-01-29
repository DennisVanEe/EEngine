#pragma once

#include "ee_Sound.hpp"

namespace eeGames
{
	class SoundMusic : public Sound
	{
	private:
		sf::Music _m_sound;
	public:
		bool assignSoundDirectory(const std::string &_p_directory)
		{
			if (!_m_sound.openFromFile(_p_directory))
				return false;
			return true;
		}

		virtual void play()
		{
			_m_sound.play();
		}
		virtual void play(uint32_t _p_startTime)
		{
			_m_sound.play();
			_m_sound.setPlayingOffset(sf::milliseconds(_p_startTime));
		}
		virtual void setLoop(bool _p_loopStatus)
		{
			_m_sound.setLoop(_p_loopStatus);
		}
		virtual void pause()
		{
			_m_sound.pause();
		}
		virtual void stop()
		{
			_m_sound.stop();
		}

		virtual void setPosition(float x, float y, float z)
		{
			_m_sound.setPosition(x, y, z);
		}
		virtual float getPositionX() const
		{
			return _m_sound.getPosition().x;
		}
		virtual float getPositionY() const
		{
			_m_sound.getPosition.y;
		}
		virtual float getPositionZ() const
		{
			return _m_sound.getPosition().z;
		}
		virtual uint32_t getPlayPosition() const
		{
			return _m_sound.getPlayingOffset().asMilliseconds();
		}
		virtual bool getLoopStatus() const
		{
			return _m_sound.getLoop();
		}

		virtual void setVolume(uint8_t _p_volume)
		{
			if (_p_volume > 100)
				_p_volume = 100;
			_m_sound.setVolume(_p_volume);
		}
	};
}
