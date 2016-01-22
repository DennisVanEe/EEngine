#include "ee_Animator.hpp"

bool eeGames::Animation::createFrames()
{
	uint8_t x, y, x1, y1;
	x = y = 0;
	if (_m_frameSize == sf::Vector2f(0, 0) || _m_columnsRows == sf::Vector2f(0, 0))
		return false;
	for (uint8_t row = 0; row < _m_columnsRows.y; row++)
	{
		for (uint8_t column = 0; column < _m_columnsRows.x; column++)
		{
			std::unique_ptr<sf::Sprite> sprite(new sf::Sprite());
			sprite->setTexture(*_m_spriteSheet);
			sprite->setTextureRect(sf::IntRect(x, y, _m_frameSize.x, _m_frameSize.y));
			_m_frames.push_back(std::move(sprite));
			x += _m_frameSize.x;
		}
		y += _m_frameSize.y;
		x = 0;
	}
}

void eeGames::Animation::play(uint16_t _p_frame)
{
	if (_p_frame + _m_currentTime > _p_frame)
	{
		_m_currentTime = _p_frame + _m_currentTime - _m_frameTime;
		if (_m_currentFrame + 1 >= _m_frames.size())
			_m_currentFrame = 0;
		_m_currentFrame++;
	}
	else
		_m_currentTime = _m_currentTime + _p_frame;
}