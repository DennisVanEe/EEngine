#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>

namespace eeGames
{
	class ResourceEngine
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<sf::Texture>> _m_textures;
		std::unordered_map<std::string, std::unique_ptr<sf::Font>> _m_fonts;
		std::unordered_map<std::string, std::unique_ptr<sf::SoundBuffer>> _m_sounds;
	public:
		ResourceEngine(const ResourceEngine&) = delete;
		const ResourceEngine &operator=(const ResourceEngine&) = delete;

		bool loadTexture(const std::string &_p_id, const std::string &_p_directory);
		bool loadFont(const std::string &_p_id, const std::string &_p_directory);
		bool loadSound(const std::string &_p_id, const std::string &_p_directory);

		bool deleteTexture(const std::string &_p_id);
		bool deleteFont(const std::string &_p_id);
		bool deleteSound(const std::string &_p_id);

		// resources can be changed
		sf::Texture *getTexture(const std::string &_p_id);
		sf::Font *getFont(const std::string &_p_id);
		sf::SoundBuffer *getSound(const std::string &_p_id);
	};
}
