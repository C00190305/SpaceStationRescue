#include "SFML/Graphics.hpp"
#include "player.h"
#include "Level.h"

int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1600, 900), "Space Station Rescue");
	window->setFramerateLimit(60);
	
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
		
		//end update


		window->clear();

		player->draw(*window);
		level.draw(*window);

		window->display();
	}

	return 0;
}