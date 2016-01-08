#pragma once

#include <iostream>
#include <string>

namespace eeGames
{
	void consoleInterface(int argc, char *argv[]);
	void printEngineInfo();

	std::string getLXMLD();
	std::string getRXMLD();
	std::string getLevelToLoad();
	int getWinX();
	int getWinY();
}

