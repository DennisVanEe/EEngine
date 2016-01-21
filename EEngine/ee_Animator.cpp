#include "ee_Animator.hpp"

bool eeGames::Animation::create_frames()
{
	uint8_t x, y, x1, y1;
	x = y = 0;
	if (frame_size == sf::Vector2f(0, 0) || columns_rows == sf::Vector2f(0, 0))
		return false;
	for (uint8_t r = 0; r < columns_rows.y; r++)
	{
		for (uint8_t c = 0; c < columns_rows.x; c++)
		{
			std::unique_ptr<sf::Sprite> sprite(new sf::Sprite());
			sprite->setTexture(*sprite_sheet);
			sprite->setTextureRect(sf::IntRect(x, y, frame_size.x, frame_size.y));
			frames.push_back(std::move(sprite));
			x += frame_size.x;
		}
		y += frame_size.y;
		x = 0;
	}
}

void eeGames::Animation::play(uint16_t frame)
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
}