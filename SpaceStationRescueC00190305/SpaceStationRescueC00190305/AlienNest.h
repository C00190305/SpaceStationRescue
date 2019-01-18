#pragma once
#include "SFML/Graphics.hpp"
#include "Sweeper.h"
#include "player.h"
#include "worker.h"
#include "NestMissile.h"

#include <vector>

#ifndef ALIENNEST_H
#define ALIENNEST_H

class AlienNest
{
public:
	AlienNest();
	AlienNest(sf::Vector2f position);

	void update(Player* p, std::vector<Worker*> workerVector);
	void draw(sf::RenderWindow &window);
	bool isAlive();
	NestMissile* getMissile();
	void reduceHealth(int amount);
	sf::Sprite getSprite();
	sf::CircleShape getCollisionRadius();
	std::vector<Sweeper*> getSweepers();
private:
	sf::Vector2f m_pos;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	std::vector<Sweeper*> m_sweepers;
	bool m_alive;
	NestMissile* m_missile;
	sf::CircleShape m_detectionRadius; //circle for detecting the player
	sf::CircleShape m_collisionRadius; //circle for colliding with player projectiles
	void resolveCollisions(Player *p);
	void updateSweepers(std::vector<Worker*> workerVector);
	void fireProjectile();
	void spawnSweeper();

	sf::Clock m_shootClock;
	sf::Time m_shootTimer;
	int m_shootDelay = 1000; //can only fire once per second

	sf::Clock m_spawnClock;
	sf::Time m_spawnTimer;
	int m_spawnDelay = 4000; //can only spawn one sweeper every 4 seconds, up to the maximum

	const int MAX_SWEEPERS = 2; //maximum number of predators that can be spawned 
	int m_health = 4; //number of hits the nest can take before being destroyed
};


#endif