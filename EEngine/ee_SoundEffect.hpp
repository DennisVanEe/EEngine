#pragma once

#include "ee_Sound.hpp"

namespace eeGames
{
	class SoundEffect : public Sound
	{
	private:
		sf::Sound m_sound;
	public:
		bool assignSoundBuffer(const sf::SoundBuffer *_p_soundBuffer)
		{
			if (!_p_soundBuffer)
				return false;
			m_sound.setBuffer(*_p_soundBuffer);
			return true;
		}

		virtual void play()
		{
			m_sound.play();
		}
		virtual void play(uint32_t startTime)
		{
			m_sound.play();
			m_sound.setPlayingOffset(sf::milliseconds(startTime));
		}
		virtual void setLoop(bool loopStatus)
		{
			m_sound.setLoop(loopStatus);
		}
		virtual void pause()
		{
			m_sound.pause();
		}
		virtual void stop()
		{
			m_sound.stop();
		}

		virtual void setPosition(float x, float y, float z)
		{
			m_sound.setPosition(x, y, z);
		}
		virtual float getPositionX() const
		{
			return m_sound.getPosition().x;
		}
		virtual float getPositionY() const
		{
			return m_sound.getPosition().y;
		}
		virtual float getPositionZ() const
		{
			return m_sound.getPosition().z;
		}
		virtual uint32_t getPlayPosition() const
		{
			return m_sound.getPlayingOffset().asMilliseconds();
		}
		virtual bool getLoopStatus() const
		{
			return m_sound.getLoop();
		}

		virtual void setVolume(uint32_t volume)
		{
			if (volume > 100)
				volume = 100;
			m_sound.setVolume(volume);
		}
	};
}
