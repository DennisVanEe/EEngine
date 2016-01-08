#include "ee_ResourceEngine.hpp"

eeGames::ResourceEngine::~ResourceEngine()
{
	for (std::pair<std::string, sf::Texture*> t : textures)
		delete t.second;
	for (std::pair<std::string, sf::Font*> f : fonts)
		delete f.second;
	for (std::pair<std::string, sf::SoundBuffer*> s : sounds)
		delete s.second;
}

bool eeGames::ResourceEngine::load_texture(const std::string & id, const std::string & dir)
{
	sf::Texture *text = new sf::Texture();
	if (!text->loadFromFile(dir))
		return false;
	textures.insert(std::make_pair(id, text));
	return true;
}

bool eeGames::ResourceEngine::load_font(const std::string & id, const std::string & dir)
{
	sf::Font *font = new sf::Font();
	if (!font->loadFromFile(dir))
		return false;
	fonts.insert(std::make_pair(id, font));
	return true;
}

bool eeGames::ResourceEngine::load_sound(const std::string & id, const std::string & dir)
{
	sf::SoundBuffer *sound = new sf::SoundBuffer();
	if (!sound->loadFromFile(dir))
		return false;
	sounds.insert(std::make_pair(id, sound));
	return true;
}

bool eeGames::ResourceEngine::delete_texture(const std::string & id)
{
	auto t = textures.find(id);
	if (t == textures.end())
		return false;
	delete t->second;
	textures.erase(t);
	return true;
}

bool eeGames::ResourceEngine::delete_font(const std::string & id)
{
	auto f = fonts.find(id);
	if (f == fonts.end())
		return false;
	delete f->second;
	fonts.erase(f);
	return true;
}

bool eeGames::ResourceEngine::delete_sound(const std::string & id)
{
	auto s = sounds.find(id);
	if (s == sounds.end())
		return false;
	delete s->second;
	sounds.erase(s);
	return true;
}

sf::Texture * eeGames::ResourceEngine::get_texture(const std::string & id)
{
	auto t = textures.find(id);
	if (t == textures.end())
		return nullptr;
	return t->second;
}

sf::Font * eeGames::ResourceEngine::get_font(const std::string & id)
{
	auto f = fonts.find(id);
	if (f == fonts.end())
		return nullptr;
	return f->second;
}

sf::SoundBuffer * eeGames::ResourceEngine::get_sound(const std::string & id)
{
	auto s = sounds.find(id);
	if (s == sounds.end())
		return nullptr;
	return s->second;
}

