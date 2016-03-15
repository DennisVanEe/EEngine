#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

namespace eeGames
{
	class Animation
	{
	private:
		const sf::Texture *m_spriteSheet;
		std::vector<std::unique_ptr<sf::Sprite>> m_frames;
		sf::Vector2u m_frameSize, m_columnsRows;
		uint32_t m_frameNum;

		// time units
		uint16_t m_frameTime, m_currentTime;
		uint16_t m_currentFrame;
	public:
		Animation() : m_spriteSheet(nullptr), m_currentFrame(0), m_frameTime(0), m_frameSize(0, 0),
			m_columnsRows(0, 0), m_frameNum(0)
		{
		}

		Animation(const Animation &copy)
		{
			m_spriteSheet = copy.m_spriteSheet; // copy the pointer
			m_frameSize = copy.m_frameSize;
			m_columnsRows = copy.m_columnsRows;
			m_frameTime = copy.m_frameTime;
			m_currentTime = copy.m_currentTime;
			m_currentFrame = copy.m_currentFrame;
			m_frameNum = copy.m_frameNum;

			m_frames.clear(); 
			for (auto &it : copy.m_frames)
			{
				m_frames.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(*it.get())));
			}

		}
		const Animation &operator=(const Animation &copy)
		{
			m_spriteSheet = copy.m_spriteSheet; // copy the pointer
			m_frameSize = copy.m_frameSize;
			m_columnsRows = copy.m_columnsRows;
			m_frameTime = copy.m_frameTime;
			m_currentTime = copy.m_currentTime;
			m_currentFrame = copy.m_currentFrame;
			m_frameNum = copy.m_frameNum;

			m_frames.clear();
			for (auto &it : copy.m_frames)
			{
				m_frames.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(*it.get())));
			}
			return *this;
		}

		bool createFrames(); // create the frames using the values

		bool setSpriteSheet(const sf::Texture *texture, uint32_t columns, uint32_t rows, uint32_t frameNum)
		{
			if (texture == nullptr)
				return false;
			m_spriteSheet = texture;
			m_columnsRows = sf::Vector2u(columns, rows);
			m_frameSize = sf::Vector2u(m_spriteSheet->getSize().x / columns, m_spriteSheet->getSize().y / rows);
			return true;
		}

		void setFrameTime(uint32_t frameTime)
		{
			m_frameTime = frameTime;
		}
		void setCurrentFrame(uint32_t frame)
		{
			if (frame >= m_frameNum)
				frame = m_frameNum - 1;
			m_currentFrame = frame;
		}
		
		uint32_t getFrameTime() const
		{
			return m_frameTime;
		}

		void play(uint32_t frameTime);

		const sf::Sprite &getCurrentFrame() const
		{
			return *m_frames[m_currentFrame];
		}
	};
}
