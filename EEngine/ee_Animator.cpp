#include "ee_Animator.hpp"

bool eeGames::Animation::createFrames()
{
	uint32_t x, y, x1, y1;
	x = y = 0;
	if (m_frameSize == sf::Vector2u(0, 0) || m_columnsRows == sf::Vector2u(0, 0))
		return false;

	uint32_t totalFrames = 0;
	for (uint32_t row = 0; row < m_columnsRows.y && totalFrames < m_frameNum; row++)
	{
		for (uint32_t column = 0; column < m_columnsRows.x && totalFrames < m_frameNum; column++)
		{
			std::unique_ptr<sf::Sprite> sprite(new sf::Sprite());
			sprite->setTexture(*m_spriteSheet);
			sprite->setTextureRect(sf::IntRect(x, y, m_frameSize.x, m_frameSize.y));
			m_frames.push_back(std::move(sprite));
			totalFrames++;
			x += m_frameSize.x;
		}
		y += m_frameSize.y;
		x = 0;
	}
}

void eeGames::Animation::play(uint32_t frameTime)
{
	if (frameTime + m_currentTime > frameTime)
	{
		m_currentTime = frameTime + m_currentTime - m_frameTime;
		if (m_currentFrame + 1 >= m_frames.size())
			m_currentFrame = 0;
		m_currentFrame++;
	}
	else
		m_currentTime = m_currentTime + frameTime;
}