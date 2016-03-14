#pragma once

#include <Thor/Resources.hpp>
#include <string>
#include <SFML/Audio.hpp>
#include <tinyxml2.h>

#include "ee_XMLContainer.hpp"
#include "ee_SoundMusic.hpp"
#include "ee_KeyedData.hpp"

namespace eeGames
{
	class MusicContainer : public XMLDocument
	{
	private:
		KeyedData<std::string, SoundMusic> m_musicList;

	public:
		MusicContainer() {}
		MusicContainer(const MusicContainer& ent) = delete;
		MusicContainer& operator=(const MusicContainer& ent) = delete;

		bool processContainer(thor::ResourceHolder<sf::Music, std::string> *holder);

		SoundMusic *getSound(const std::string &id)
		{
			auto it = m_musicList.find(id);
			if (it == m_musicList.end())
				throw std::logic_error("The music " + id + " could not be found");
			return &it->second;
		}
		const SoundMusic *getSound(const std::string &id) const
		{
			auto it = m_musicList.find(id);
			if (it == m_musicList.end())
				throw std::logic_error("The music " + id + " could not be found");
			return &it->second;
		}
	};
}