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
		sf::Vector2f m_frameSize, m_columnsRows;

		// time units
		uint16_t m_frameTime, m_currentTime;
		uint16_t m_currentFrame;
	public:
		Animation() : m_spriteSheet(nullptr), m_currentFrame(0), m_frameTime(0), m_frameSize(0, 0),
			m_columnsRows(0, 0)
		{
		}

		Animation(const Animation& copy)
		{
			m_spriteSheet = copy.m_spriteSheet;
			m_frameSize = copy.m_frameSize;
			m_columnsRows = copy.m_columnsRows;
			m_frameTime = copy.m_frameTime;
			m_currentTime = copy.m_currentTime;
			m_currentFrame = copy.m_currentFrame;

			for (auto &frameIterator : copy.m_frames)
			{
				m_frames.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(*frameIterator.get())));
			}

		}
		const Animation &operator=(const Animation &copy)
		{
			Animation(copy);
			return *this;
		}

		void setFrameSize(uint32_t _p_width, uint32_t _p_height) // sets the size of each sprite on the sprite sheet
		{
			m_frameSize = sf::Vector2f(_p_width, _p_height);
		}
		void setColumnsRows(uint8_t _p_columns, uint8_t _p_rows) // set the number of columns and rows in the sprite sheet
		{
			m_columnsRows = sf::Vector2f(_p_columns, _p_rows);
		}
		bool createFrames(); // create the frames using the values

		bool setSpriteSheet(const sf::Texture *_p_texture)
		{
			if (_p_texture == nullptr)
				return false;
			m_spriteSheet = _p_texture;
			return true;
		}

		void setFrameTime(uint16_t _p_frameTime)
		{
			m_frameTime = _p_frameTime;
		}
		void setCurrentFrame(uint16_t _p_frame)
		{
			m_currentFrame = _p_frame;
		}
		uint16_t getFrameTime() const
		{
			return m_frameTime;
		}

		void play(uint16_t _p_frameTime);
		const sf::Sprite &getCurrentFrame() const
		{
			return *m_frames[m_currentFrame];
		}
	};
}
