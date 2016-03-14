#pragma once

#include <SFML/Audio.hpp>
#include <tinyxml2.h>
#include <Thor\Resources.hpp>

#include "ee_KeyedData.hpp"
#include "ee_SoundEffect.hpp"
#include "ee_XMLContainer.hpp"

namespace eeGames
{
	class SoundContainer : public XMLDocument
	{
	private:
		KeyedData<std::string, SoundEffect> m_soundBuffers;

	public:
		SoundContainer() {}
		SoundContainer(const SoundContainer& ent) = delete;
		SoundContainer& operator=(const SoundContainer& ent) = delete;

		bool processContainer(thor::ResourceHolder<sf::SoundBuffer, std::string> *holder);

		SoundEffect *getSound(const std::string &id)
		{
			auto it = m_soundBuffers.find(id);
			if (it == m_soundBuffers.end())
				throw std::logic_error("The sound " + id + " could not be found");
			return &it->second;
		}
		const SoundEffect *getSound(const std::string &id) const
		{
			auto it = m_soundBuffers.find(id);
			if (it == m_soundBuffers.end())
				throw std::logic_error("The sound " + id + " could not be found");
			return &it->second;
		}
	};
}
