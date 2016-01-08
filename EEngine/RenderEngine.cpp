#include "stdafx.h"
#include "RenderEngine.hpp"

void eeGames::RenderEngine::setWindow(Window & rt)
{
	renderWindow = &rt;
}

void eeGames::RenderEngine::setLevel(Level & lev)
{
	level = &lev;
	renderWindow->setView(level->getView());
	level->setUpForRendering();
}