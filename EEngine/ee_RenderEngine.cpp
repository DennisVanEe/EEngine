#include "ee_RenderEngine.hpp"

void eeGames::RenderEngine::draw(uint16_t frame_time) const
{
	for (auto ent : entities)
	{
		ent.second->draw(frame_time, window);
	}
}