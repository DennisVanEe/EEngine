#include "ee_Animator.hpp"

eeGames::Animation::Animation(sf::RenderWindow *rw) : render_window(rw), sprite_sheet(nullptr), current_frame(0), frame_time(0), frame_size(0, 0),
	columns_rows(0, 0)
{
}

eeGames::Animation::~Animation()
{
	for (sf::Sprite *sp : frames)
		delete sp;
}

void eeGames::Animation::set_frame_size(unsigned int width, unsigned int height)
{
	frame_size = sf::Vector2f(width, height);
}

void eeGames::Animation::set_columns_rows(unsigned int columns, unsigned int row)
{
	columns_rows = sf::Vector2f(columns, row);
}

bool eeGames::Animation::create_frames()
{
	unsigned int x, y, x1, y1;
	x = y = 0;
	if (frame_size == sf::Vector2f(0, 0) || columns_rows == sf::Vector2f(0, 0))
		return false;
	for (int r = 0; r < columns_rows.y; r++)
	{
		for (int c = 0; c < columns_rows.x; c++)
		{
			sf::Sprite *sprite = new sf::Sprite();
			sprite->setTexture(*sprite_sheet);
			frames.push_back(sprite);
			sprite->setTextureRect(sf::IntRect(x, y, frame_size.x, frame_size.y));
			x += frame_size.x;
		}
		y += frame_size.y;
		x = 0;
	}
}

bool eeGames::Animation::set_sprite_sheet(sf::Texture *text)
{
	if (text == nullptr)
		return false;
	sprite_sheet = text;
	return true;
}

void eeGames::Animation::set_frame_time(unsigned int fr)
{
	frame_time = fr;
}

void eeGames::Animation::set_position(int x, int y)
{
	position = sf::Vector2f(x, y);
}

sf::Texture *eeGames::Animation::get_sprite_sheet() const
{
	return sprite_sheet;
}

unsigned int eeGames::Animation::get_frame_time() const
{
	return frame_time;
}

void eeGames::Animation::play(unsigned int frame)
{
	if (frame + current_time > frame_time)
	{
		current_time = frame + current_time - frame_time;
		if (current_frame + 1 >= frames.size())
			current_frame = 0;
		current_frame++;
	}
	else
		current_time = current_time + frame;
	
	frames[current_frame]->setPosition(position);
	render_window->draw(*frames[current_frame]);
}

void eeGames::Animation::restart()
{
	current_frame = 0;
}