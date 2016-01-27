#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

namespace eeGames
{
	class Animation
	{
	private:
		const sf::Texture *_m_spriteSheet;
		std::vector<std::unique_ptr<sf::Sprite>> _m_frames;
		sf::Vector2f _m_frameSize, _m_columnsRows;

		// time units
		uint16_t _m_frameTime, _m_currentTime;
		uint16_t _m_currentFrame;
	public:
		Animation() : sprite_sheet(nullptr), current_frame(0), frame_time(0), frame_size(0, 0),
			columns_rows(0, 0)
		{
		}

		Animation(const Animation& _p_copiedAnimation) 
		{
			_m_spriteSheet = _p_copiedAnimation._m_spriteSheet;
			_m_frameSize = _p_copiedAnimation._m_frameSize;
			_m_columnsRows = _p_copiedAnimation._m_columnsRows;
			_m_frameTime = _p_copiedAnimation._m_frameTime;
			_m_currentTime = _p_copiedAnimation._m_currentTime;
			_m_currentFrame = _p_copiedAnimation._m_currentFrame;

			for (auto &frameIterator : _p_copiedAnimation._m_frames)
			{
				_m_frames.push_back(std::unique_ptr<sf::Sprite>(new sf::Sprite(*frameIterator.get())));
			}

		}
		void operator=(const Animation&) = delete;

		void setFrameSize(uint32_t _p_width, uint32_t _p_height) // sets the size of each sprite on the sprite sheet
		{
			_m_frameSize = sf::Vector2f(_p_width, _p_height);
		}
		void setColumnsRows(uint8_t _p_columns, uint8_t _p_rows) // set the number of columns and rows in the sprite sheet
		{
			_m_columnsRows = sf::Vector2f(_p_columns, _p_rows);
		}
		bool createFrames(); // create the frames using the values

		bool setSpriteSheet(const sf::Texture *_p_texture)
		{
			if (_p_texture == nullptr)
				return false;
			_m_spriteSheet = _p_texture;
			return true;
		}

		void setFrameTime(uint16_t _p_frameTime)
		{
			_m_frameTime = _p_frameTime;
		}
		void setCurrentFrame(uint16_t _p_frame)
		{
			_m_currentFrame = _p_frame;
		}
		uint16_t getFrameTime() const
		{
			return _m_frameTime;
		}

		void play(uint16_t _p_frameTime);
		const sf::Sprite &getCurrentFrame() const
		{
			return *_m_frames[_m_currentFrame];
		}
	};
}
