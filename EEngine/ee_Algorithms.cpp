#include "stdafx.h"
#include "ee_Algorithms.hpp"

std::string eeGames::parseDir(const std::string & dir)
{
	std::string name;
	for (int i = dir.size() - 1; i >= 0 && dir[i] != '\\' && dir[i] != '/'; i--)
	{
		name += dir[i];
	}
	std::reverse(name.begin(), name.end());
	return std::move(name);
}
