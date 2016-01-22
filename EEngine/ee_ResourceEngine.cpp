#include "ee_ResourceEngine.hpp"

bool eeGames::ResourceEngine::loadTexture(const std::string &_p_id, const std::string &_p_directory)
{
	std::unique_ptr<sf::Texture> _tmp_texture(new sf::Texture());
	if (!_tmp_texture->loadFromFile(_p_directory))
		return false;
	_m_textures.insert(std::make_pair(_p_id, std::move(_tmp_texture)));
	return true;
}

bool eeGames::ResourceEngine::loadFont(const std::string &_p_id, const std::string &_p_directory)
{
	std::unique_ptr<sf::Font> _tmp_font(new sf::Font());
	if (!_tmp_font->loadFromFile(_p_directory))
		return false;
	_m_fonts.insert(std::make_pair(_p_id, std::move(_tmp_font)));
	return true;
}

bool eeGames::ResourceEngine::loadSound(const std::string &_p_id, const std::string &_p_directory)
{
	std::unique_ptr<sf::SoundBuffer> _tmp_soundBuffer(new sf::SoundBuffer());
	if (!_tmp_soundBuffer->loadFromFile(_p_directory))
		return false;
	_m_sounds.insert(std::make_pair(_p_id, std::move(_tmp_soundBuffer)));
	return true;
}

bool eeGames::ResourceEngine::deleteTexture(const std::string &_p_id)
{
	auto _tmp_textureIterator = _m_textures.find(_p_id);
	if (_tmp_textureIterator == _m_textures.end())
		return false;
	_tmp_textureIterator->second.release;
	_m_textures.erase(_tmp_textureIterator);
	return true;
}

bool eeGames::ResourceEngine::deleteFont(const std::string &_p_id)
{
	auto _tmp_fontIterator = _m_fonts.find(_p_id);
	if (_tmp_fontIterator == _m_fonts.end())
		return false;
	_tmp_fontIterator->second.release();
	_m_fonts.erase(_tmp_fontIterator);
	return true;
}

bool eeGames::ResourceEngine::deleteSound(const std::string &_p_id)
{
	auto _tmp_soundIterator = _m_sounds.find(_p_id);
	if (_tmp_soundIterator == _m_sounds.end())
		return false;
	_tmp_soundIterator->second.release();
	_m_sounds.erase(_tmp_soundIterator);
	return true;
}

sf::Texture *eeGames::ResourceEngine::getTexture(const std::string &_p_id)
{
	auto _tmp_textureIterator = _m_textures.find(_p_id);
	if (_tmp_textureIterator == _m_textures.end())
		return nullptr;
	return _tmp_textureIterator->second.get();
}

sf::Font *eeGames::ResourceEngine::getFont(const std::string &_p_id)
{
	auto _tmp_fontIterator = _m_fonts.find(_p_id);
	if (_tmp_fontIterator == _m_fonts.end())
		return nullptr;
	return _tmp_fontIterator->second.get();
}

sf::SoundBuffer *eeGames::ResourceEngine::getSound(const std::string &_p_id)
{
	auto _tmp_soundIterator = _m_sounds.find(_p_id);
	if (_tmp_soundIterator == _m_sounds.end())
		return nullptr;
	return _tmp_soundIterator->second.get();
}

