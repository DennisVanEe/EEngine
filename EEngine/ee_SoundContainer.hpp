#pragma once

// EEngine Copyright (c) 2016
// ee_SoundContainer.hpp
// --------------------------------------------------------
// A container used to manage sound objects in the world.
// SoundEffect and SoundMusic objects are managed and owned
// by an object of this type. Access is granted to others
// (such as a script module) to manipulate these objects.

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>

#include "ee_Sound.hpp"
#include "ee_SoundEffect.hpp"
#include "ee_SoundMusic.hpp"

namespace eeGames
{
	enum class _e_SoundType { EFFECT, MUSIC };

	class SoundContainer
	{
	private:
		struct _str_Sound
		{
			std::unique_ptr<Sound> _m_sound;
			_e_SoundType _m_type;
			_str_Sound(std::unique_ptr<Sound> _p_sound, _e_SoundType _p_soundType) : _m_sound(std::move(_p_sound)), _m_type(_p_soundType) {}
		};
	private:
		std::unordered_map <std::string, _str_Sound> _m_soundList;
	public:
		SoundEffect *createSoundEffect(const std::string &_p_id, const sf::SoundBuffer *_p_soundBuffer)
		{
			std::unique_ptr<Sound> sound(new SoundEffect());
			SoundEffect *returnSound = static_cast<SoundEffect*>(sound.get());
			if (returnSound->assignSoundBuffer(_p_soundBuffer))
				return nullptr;
			_m_soundList.insert(std::make_pair(_p_id, _str_Sound(std::move(sound), _e_SoundType::EFFECT)));
			return returnSound;
		}
		SoundMusic *createSoundMusic(const std::string &_p_id, const std::string &dir)
		{
			std::unique_ptr<Sound> sound(new SoundMusic());
			SoundMusic *returnSound = static_cast<SoundMusic*>(sound.get());
			if (!returnSound->assignSoundDirectory(dir))
				return nullptr;
			_m_soundList.insert(std::make_pair(_p_id, _str_Sound(std::move(sound), _e_SoundType::MUSIC)));
			return returnSound;
		}

		SoundEffect *getSoundEffect(const std::string &_p_id)
		{
			auto soundIterator = _m_soundList.find(_p_id);
			if (soundIterator == _m_soundList.end())
				return nullptr;
			if (soundIterator->second._m_type == _e_SoundType::EFFECT)
				return static_cast<SoundEffect *>(soundIterator->second._m_sound.get());
			return nullptr;
		}
		SoundMusic *getSoundMusic(const std::string &_p_id)
		{
			auto soundIterator = _m_soundList.find(_p_id);
			if (soundIterator == _m_soundList.end())
				return nullptr;
			if (soundIterator->second._m_type == _e_SoundType::MUSIC)
				return static_cast<SoundMusic *>(soundIterator->second._m_sound.get());
			return nullptr;
		}

		SoundEffect *createSoundEffectCopy(const std::string &_p_id, const std::string &_p_idNew)
		{
			SoundEffect *returnSound = getSoundEffect(_p_id);
			std::unique_ptr<Sound> sound(new SoundEffect(*returnSound));
			_m_soundList.insert(std::make_pair(_p_idNew, _str_Sound(std::move(sound), _e_SoundType::EFFECT)));
			return returnSound;
		}
	};

	// used to control the "microphone" or listner:
	float getMicrophonePositionX()
	{
		return sf::Listener::getPosition().x;
	}
	float getMicrophonePositionY()
	{
		return sf::Listener::getPosition().y;
	}
	float getMicrophonePositionZ()
	{
		return sf::Listener::getPosition().z;
	}
}
