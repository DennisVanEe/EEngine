#pragma once

#include <Thor/Resources.hpp>
#include <string>
#include <SFML/Audio.hpp>
#include <tinyxml2.h>
#include <unordered_map>

#include "ee_XMLContainer.hpp"
#include "ee_SoundMusic.hpp"

namespace eeGames
{
	class MusicContainer : public XMLDocument
	{
	private:
		std::unordered_map<std::string, SoundMusic> m_musicList;

	public:
		MusicContainer() {}
		MusicContainer(MusicContainer &&copy) :
			m_musicList(std::move(copy.m_musicList))
		{
		}
		MusicContainer(MusicContainer &) = delete;

		bool processContainer();

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