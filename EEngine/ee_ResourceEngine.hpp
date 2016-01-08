#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

namespace eeGames
{
	class ResourceEngine
	{
	private:
		std::unordered_map<std::string, sf::Texture*> textures;
		std::unordered_map<std::string, sf::Font*> fonts;
		std::unordered_map<std::string, sf::SoundBuffer*> sounds;
	public:
		~ResourceEngine(); // only the resource manager will delete resources

		bool load_texture(const std::string &id, const std::string &dir);
		bool load_font(const std::string &id, const std::string &dir);
		bool load_sound(const std::string &id, const std::string &dir);

		bool delete_texture(const std::string &id);
		bool delete_font(const std::string &id);
		bool delete_sound(const std::string &id);

		// resources can be changed
		sf::Texture *get_texture(const std::string &id);
		sf::Font *get_font(const std::string &id);
		sf::SoundBuffer *get_sound(const std::string &id);
	};
}
