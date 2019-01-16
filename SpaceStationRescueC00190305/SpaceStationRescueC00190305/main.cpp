#include "tmxlite/Config.hpp"
#include "tmxlite/Map.hpp"
#include "SFML/Graphics.hpp"
#include "player.h"
#include "Level.h"
#include "NPCManager.h"
#include "worker.h"
#include "HUD.h"

#include <iostream>
#include <vector>

int main()
{
	//Window setup
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1600, 900), "Space Station Rescue");
	window->setFramerateLimit(60);
	sf::View camera;
	camera.setSize(800, 450);
	window->setView(camera);

	//Game object declarations
	Level level("level.tmx");
	Player* player = new Player();
	HUD* hud = new HUD(level);
	NPCManager npcManager(level.getMap());


	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			{
				window->close();
			}
		}

		//update

		player->update(*window);
		hud->update(player->getPosition(), player->getScore());
		camera.setCenter(player->getPosition());
		npcManager.updateEntities(player);
		level.update(player, player->getProjectileManager(), npcManager);
		window->setView(camera);
		
		
		//end update

		//Render
		window->clear();
		
		level.draw(*window);
		npcManager.drawEntities(*window);
		player->draw(*window);
		hud->draw(*window);
		window->display();

		//End render
	}

	return 0;
}