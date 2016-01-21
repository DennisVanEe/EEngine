#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

namespace eeGames
{
	class Animation
	{
	private:
		const sf::Texture *sprite_sheet;
		std::vector<std::unique_ptr<sf::Sprite>> frames;
		sf::Vector2f frame_size, columns_rows;

		// time units
		uint16_t frame_time, current_time;
		uint16_t current_frame;
	public:
		Animation() : sprite_sheet(nullptr), current_frame(0), frame_time(0), frame_size(0, 0),
			columns_rows(0, 0)
		{
		}

		void set_frame_size(uint32_t width, uint32_t height) // sets the size of each sprite on the sprite sheet
		{
			frame_size = sf::Vector2f(width, height);
		}
		void set_columns_rows(uint8_t columns, uint8_t rows) // set the number of columns and rows in the sprite sheet
		{
			columns_rows = sf::Vector2f(columns, rows);
		}
		bool create_frames(); // create the frames using the values

		bool set_sprite_sheet(const sf::Texture *text)
		{
			if (text == nullptr)
				return false;
			sprite_sheet = text;
			return true;
		}

		void set_frame_time(uint16_t fr)
		{
			frame_time = fr;
		}
		void set_current_frame(uint16_t frame)
		{
			current_frame = frame;
		}
		uint16_t get_frame_time() const
		{
			return frame_time;
		}

		void play(uint16_t frame_time);
		const sf::Sprite &get_current_frame() const
		{
			return *frames[current_frame];
		}
	};
}
