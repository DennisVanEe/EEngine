#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace eeGames
{
	class Animation
	{
	private:
		sf::Texture *sprite_sheet;
		sf::RenderWindow *render_window;
		std::vector<sf::Sprite*> frames;
		sf::Vector2f position, frame_size, columns_rows;
		unsigned int frame_time, current_frame, current_time;
	public:
		Animation(sf::RenderWindow *rw);
		~Animation();

		void set_frame_size(unsigned int width, unsigned int height); // sets the size of each sprite on the sprite sheet
		void set_columns_rows(unsigned int columns, unsigned int rows); // set the number of columns and rows in the sprite sheet
		bool create_frames(); // create the frames using the values

		bool set_sprite_sheet(sf::Texture *text);
		void set_frame_time(unsigned int fr);
		void set_position(int x, int y);

		sf::Texture *get_sprite_sheet() const;
		unsigned int get_frame_time() const;

		void play(unsigned int frame_time);
		void restart();
	};
}
