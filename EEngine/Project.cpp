#include "Project.hpp"

bool eeGames::Project::load(const std::string & PXML)
{
	// opening and processing project file

	tinyxml2::XMLElement* element;
	std::string levelDir, resourceDir;

	if (projectFile.LoadFile(PXML.c_str()) != tinyxml2::XML_SUCCESS)
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

	element = element->NextSiblingElement();
	if (element == nullptr)
	{
		std::cout << "[error]: issue with project xml file format\n";
		return false;
	}
	std::string t_title = element->Attribute("title");

	element = element->FirstChildElement();
	if (element == nullptr)
	{
		std::cout << "[error]: issue with project xml file format\n";
		return false;
	}

	unsigned int t_resX = element->IntAttribute("x");
	unsigned int t_resY = element->IntAttribute("y");
	bool t_fullscrn = element->IntAttribute("fullscreen");
	bool t_vsync = element->IntAttribute("vsync");

	window.create(sf::Vector2u(t_resX, t_resY), t_title, t_fullscrn, t_vsync);

	// loading project object

	renderEngine.setWindow(window);
	loadEngine.load(resourceDir, levelDir);
	levels = loadEngine.getLevels();
}

void eeGames::Project::executeLevel(const std::string & levName)
{
	renderEngine.setLevel(levels.getObject(levName));

	sf::Clock time;
	unsigned int frameCounter = 0;

	while (window.isOpen())
	{
		frameCounter++;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Time elapsed = time.restart();

		if (frameCounter % 10 == 0)
			std::cout << "[FPS]: " << 1 / elapsed.asSeconds() << '/r';

		renderEngine.step(elapsed.asSeconds());
	}
}