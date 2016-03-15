#pragma once

#include <memory>

#include "ee_Sound.hpp"

namespace eeGames
{
	// TODO: resource loader for sf::Music needs to be fixed
	class SoundMusic : public Sound
	{
	private:
		std::unique_ptr<sf::Music> m_sound;
	public:
		SoundMusic() :
			m_sound(new sf::Music())
		{
		}
		SoundMusic(SoundMusic &&copy) :
			m_sound(std::move(copy.m_sound))
		{
		}
		SoundMusic(SoundMusic &) = delete;

		bool assignSoundMusic(const std::string &dir)
		{
			return m_sound->openFromFile(dir);
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
			return m_sound->getPosition().y;
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
