#pragma once

#include "ee_Sound.hpp"

namespace eeGames
{
	// TODO: resource loader for sf::Music needs to be fixed
	class SoundMusic : public Sound
	{
	private:
		sf::Music *m_sound;
	public:
		bool assignSoundMusic(sf::Music *sound)
		{
			if (sound == nullptr)
				return false;
			m_sound = sound;
			return true;
		}

		virtual void play()
		{
			m_sound->play();
		}
		virtual void play(uint32_t _p_startTime)
		{
			m_sound->play();
			m_sound->setPlayingOffset(sf::milliseconds(_p_startTime));
		}
		virtual void setLoop(bool _p_loopStatus)
		{
			m_sound->setLoop(_p_loopStatus);
		}
		virtual void pause()
		{
			m_sound->pause();
		}
		virtual void stop()
		{
			m_sound->stop();
		}

		virtual void setPosition(float x, float y, float z)
		{
			m_sound->setPosition(x, y, z);
		}
		virtual float getPositionX() const
		{
			return m_sound->getPosition().x;
		}
		virtual float getPositionY() const
		{
			m_sound->getPosition().y;
		}
		virtual float getPositionZ() const
		{
			return m_sound->getPosition().z;
		}
		virtual uint32_t getPlayPosition() const
		{
			return m_sound->getPlayingOffset().asMilliseconds();
		}
		virtual bool getLoopStatus() const
		{
			return m_sound->getLoop();
		}

		virtual void setVolume(uint32_t volume)
		{
			if (volume > 100)
				volume = 100;
			m_sound->setVolume(volume);
		}
	};
}
