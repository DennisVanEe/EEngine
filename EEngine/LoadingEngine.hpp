#pragma once

#include <assert.h>
#include <iostream>

#include "tinyxml2\tinyxml2.h"

// SFML API
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"

#include "eeContainer.hpp"
#include "Level.hpp"
#include "Entity.hpp"
#include "ScriptedEntity.hpp"

namespace eeGames
{
	class LoadingEngine
	{
	private:
		tinyxml2::XMLDocument levelXML;
		tinyxml2::XMLDocument resourceXML;

		//eeContainer<Resource<sf::SoundBuffer>> soundBufferContainer;
		eeContainer<Resource<sf::Texture>>  textureContainer;

		eeContainer<Level> levelContainer;

		bool loaded;

		bool checkXMLError(tinyxml2::XMLError result);
	public:
		LoadingEngine() : loaded(false) {}

		bool load(const std::string & RXMLD, const std::string & LXMLD);
		void loadLevels();

		eeContainer<Level> & getLevels()
		{
			if (loaded)
				return levelContainer;
			else
				// issue, levels were not loaded
				return levelContainer;
		}
		const eeContainer<Level> & getLevels() const
		{
			if (loaded)
				return levelContainer;
			else
				// issue, levels were not loaded
				return levelContainer;
		}
	};
}
