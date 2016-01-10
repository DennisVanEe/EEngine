#include "ee_Animator.hpp"

eeGames::Animation::~Animation()
{
	for (sf::Sprite *sp : frames)
		delete sp;
}

bool eeGames::Animation::create_frames()
{
	unsigned int x, y, x1, y1;
	x = y = 0;
	if (frame_size == sf::Vector2f(0, 0) || columns_rows == sf::Vector2f(0, 0))
		return false;
	for (uint8_t r = 0; r < columns_rows.y; r++)
	{
		for (uint8_t c = 0; c < columns_rows.x; c++)
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

void eeGames::Animation::play(uint16_t frame, sf::RenderWindow *target)
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
	target->draw(*frames[current_frame]);
}