
#include "ee_RequestQueue.hpp"
#include "ee_Request.hpp"
#include "ee_Animator.hpp"

#include <iostream>
#include <angelscript.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace eeGames;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "test window");
	Animation testAnimation(&window);
	sf::Texture texture;
	if (texture.loadFromFile("C:/Users/Dennis/Downloads/runningcat.png"))
		std::cout << "loaded properly\n";

	testAnimation.set_position(640, 360);
	testAnimation.set_frame_time(75);
	testAnimation.set_sprite_sheet(&texture);
	testAnimation.set_frame_size(1024 / 2, 1024 / 4);
	testAnimation.set_columns_rows(2, 4);
	testAnimation.create_frames();

	window.setVerticalSyncEnabled(true);

	sf::Clock timer;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		testAnimation.play(timer.restart().asMilliseconds());
		window.display();
	}

	std::cin.get();
	std::cin.get();
	return 0;
}
