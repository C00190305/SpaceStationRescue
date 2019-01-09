#include "tmxlite/Config.hpp"
#include "tmxlite/Map.hpp"
#include "SFML/Graphics.hpp"
#include "player.h"
#include "Level.h"

#include <iostream>
#include <vector>

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1600, 900), "Space Station Rescue");
	window->setFramerateLimit(60);
	sf::View camera;
	camera.setSize(800, 450);
	window->setView(camera);

	
	Player* player = new Player();

	Level level("level.tmx");

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		//update

		player->update(*window);
		camera.setCenter(player->getPosition());
		window->setView(camera);
		
		//end update

		window->clear();

		player->draw(*window);
		//level.draw
		level.draw(*window);

		window->display();
	}

	return 0;
}