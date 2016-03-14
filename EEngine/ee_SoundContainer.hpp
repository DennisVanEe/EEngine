#pragma once

#include <SFML/Audio.hpp>
#include <tinyxml2.h>
#include <Thor\Resources.hpp>

#include "ee_KeyedData.hpp"
#include "ee_XMLContainer.hpp"

namespace eeGames
{
	class SoundContainer : public XMLDocument
	{
	private:
		KeyedData<std::string, sf::SoundBuffer> m_soundBuffers;

	public:
		SoundContainer() {}
		SoundContainer(const SoundContainer& ent) = delete;
		SoundContainer& operator=(const SoundContainer& ent) = delete;

		bool processContainer(thor::ResourceHolder<sf::SoundBuffer, std::string> *holder);

		sf::SoundBuffer *getSound(const std::string &id)
		{
			auto it = m_soundBuffers.find(id);
			if (it == m_soundBuffers.end())
				return nullptr;
			return &it->second;
		}
		const sf::SoundBuffer *getSound(const std::string &id) const
		{
			auto it = m_soundBuffers.find(id);
			if (it == m_soundBuffers.end())
				return nullptr;
			return &it->second;
		}
	};
}
