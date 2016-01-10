#include "ee_AnimatedEntity.hpp"

void eeGames::AnimatedEntity::assign_texture(sf::Texture *text, uint32_t width, uint32_t height, uint8_t columns, uint8_t rows)
{
	sprite.set_sprite_sheet(text);
	sprite.set_frame_size(width, height);
	sprite.set_columns_rows(columns, rows);
	sprite.create_frames();
}