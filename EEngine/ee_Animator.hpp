#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace eeGames
{
	class Animation
	{
	private:
		sf::Texture *sprite_sheet;
		std::vector<sf::Sprite*> frames;
		sf::Vector2f position, frame_size, columns_rows;
		uint16_t frame_time, current_time; 
		uint16_t current_frame;
	public:
		Animation() : sprite_sheet(nullptr), current_frame(0), frame_time(0), frame_size(0, 0),
			columns_rows(0, 0)
		{
		}
		~Animation();

		void set_frame_size(uint32_t width, uint32_t height) // sets the size of each sprite on the sprite sheet
		{
			frame_size = sf::Vector2f(width, height);
		}
		void set_columns_rows(uint8_t columns, uint8_t rows) // set the number of columns and rows in the sprite sheet
		{
			columns_rows = sf::Vector2f(columns, rows);
		}
		bool create_frames(); // create the frames using the values

		bool set_sprite_sheet(sf::Texture *text);

		void set_frame_time(uint16_t fr)
		{
			frame_time = fr;
		}
		void set_position(int x, int y)
		{
			position = sf::Vector2f(x, y);
		}
		sf::Texture *get_sprite_sheet() const
		{
			return sprite_sheet;
		}
		uint16_t get_frame_time() const
		{
			return frame_time;
		}

		void play(uint16_t frame_time, sf::RenderWindow *target);
		void set_current_frame(uint16_t frame)
		{
			current_frame = frame;
		}
	};
}
