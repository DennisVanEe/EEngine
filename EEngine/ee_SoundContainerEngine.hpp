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
#include <Thor\Resources.hpp>

#include "ee_SoundContainer.hpp"
#include "ee_MusicContainer.hpp"

namespace eeGames
{
	class SoundContainerEngine
	{
	private:
		std::unordered_map<std::string, SoundContainer> m_soundContainers;
		std::unordered_map<std::string, MusicContainer> m_musicContainers;

		thor::ResourceHolder<sf::SoundBuffer, std::string> m_soundBuffersRes;

	public:
		void loadSoundContainer(const std::string &id, const std::string &dir)
		{			
		   	auto pair = m_soundContainers.insert(std::make_pair(id, SoundContainer()));
			if (pair.second == false)
				throw std::runtime_error("could not insert sound container " + id);
			pair.first->second.loadContainer(dir);
			pair.first->second.processContainer(&m_soundBuffersRes);
		}
		void removeSoundContainer(const std::string &id)
		{
			auto it = m_soundContainers.find(id);
			if (it == m_soundContainers.end())
				throw std::logic_error("could not find sound container " + id);

			m_soundContainers.erase(it);
		}

		void loadMusicContainer(const std::string &id, const std::string &dir)
		{
			auto pair = m_musicContainers.insert(std::make_pair(id, MusicContainer()));
			if (pair.second == false) 
				throw std::runtime_error("could not insert music container " + id);
			pair.first->second.loadContainer(dir);
			pair.first->second.processContainer();
		}
		void removeMusicContainer(const std::string &id)
		{
			auto it = m_musicContainers.find(id);
			if (it == m_musicContainers.end())
				throw std::logic_error("could not find music container " + id);

			m_musicContainers.erase(it);
		}

		SoundEffect *getSoundEffect(const std::string &contID, const std::string &soundID)
		{
			auto it = m_soundContainers.find(contID);
			if (it == m_soundContainers.end())
				throw std::logic_error("could not find sound container " + contID);

			return it->second.getSound(soundID);
		}
		SoundMusic *getSoundMusic(const std::string &contID, const std::string &musicID)
		{
			auto it = m_musicContainers.find(contID);
			if (it == m_musicContainers.end())
				throw std::logic_error("could not find music container " + contID);

			return it->second.getSound(musicID);
		}
	};

	// used to control the "microphone" or listner:
	extern float getMicrophonePositionX();
	float getMicrophonePositionY();
	float getMicrophonePositionZ();
}
