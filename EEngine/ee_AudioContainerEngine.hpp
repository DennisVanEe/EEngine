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
	class AudioContainerEngine
	{
	private:
		KeyedData<std::string, SoundContainer> m_soundContainers;
		KeyedData<std::string, MusicContainer> m_musicContainers;

		thor::ResourceHolder<sf::SoundBuffer, std::string> m_soundBuffersRes;
		thor::ResourceHolder<sf::Music, std::string> m_musicRes;

	public:
		bool loadSoundContainer(const std::string &id, const std::string &dir)
		{
			auto it = m_soundContainers.find(id);
			if (it == m_soundContainers.end())
				return false;
			
		   	auto pair = m_soundContainers.insert(std::make_pair(id, SoundContainer()));
			if (pair.second == false) return false;
			if (pair.first->second.loadContainer(dir) == false) return  false;
			pair.first->second.processContainer(&m_soundBuffersRes);
		}
		bool removeSoundContainer(const std::string &id)
		{
			auto it = m_soundContainers.find(id);
			if (it == m_soundContainers.end())
				return false;

			m_soundContainers.erase(it);
			return true;
		}

		bool loadMusicContainer(const std::string &id, const std::string &dir)
		{
			auto it = m_musicContainers.find(id);
			if (it == m_musicContainers.end())
				return false;

			auto pair = m_musicContainers.insert(std::make_pair(id, MusicContainer()));
			if (pair.second == false) return false;
			if (pair.first->second.loadContainer(dir) == false) return false;
			return pair.first->second.processContainer(&m_musicRes);
		}
		bool removeMusicContainer(const std::string &id)
		{
			auto it = m_musicContainers.find(id);
			if (it == m_musicContainers.end())
				return false;

			m_musicContainers.erase(it);
			return true;
		}

		sf::SoundBuffer *getSound(const std::string &contID, const std::string &soundID)
		{
			auto it = m_soundContainers.find(contID);
			if (it == m_soundContainers.end())
				return false;

			return it->second.getSound(soundID);
		}
		sf::Music *getMusic(const std::string &contID, const std::string &musicID)
		{
			auto it = m_musicContainers.find(contID);
			if (it == m_musicContainers.end())
				return false;

			return it->second.getSound(musicID);
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
