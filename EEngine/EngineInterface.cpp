#include "EngineInterface.h"

bool eeGames::EngineInterface::loadProject(const std::string & XMLDIR)
{
	// opening and processing project file

	tinyxml2::XMLElement* element;
	std::string levelDir, resourceDir;

	if (projectFile.LoadFile(XMLDIR.c_str()) != tinyxml2::XML_SUCCESS)
	{
		std::cout << "[error]: issue parsing or opening project xml file\n";
		return false;
	}

	element = projectFile.FirstChildElement()->FirstChildElement();
	if (element == nullptr)
	{
		std::cout << "[error]: issue with project xml file format\n";
		return false;
	}
	levelDir = element->Attribute("dir");
	
	element = element->NextSiblingElement();
	if (element == nullptr)
	{
		std::cout << "[error]: issue with project xml file format\n";
		return false;
	}
	resourceDir = element->Attribute("dir");

	// loading project object


}