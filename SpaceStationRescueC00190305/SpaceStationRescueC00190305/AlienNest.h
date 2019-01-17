#pragma once
#include "SFML/Graphics.hpp"
#include "Predator.h"
#include "player.h"
#include "NestMissile.h"

#include <vector>

#ifndef ALIENNEST_H
#define ALIENNEST_H

class AlienNest
{
public:
	AlienNest();
	AlienNest(sf::Vector2f position);

	void update(Player* p);
	void draw(sf::RenderWindow &window);
	bool isAlive();
	NestMissile getMissile();
private:
	sf::Vector2f m_pos;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	std::vector<Predator*> m_predators;
	bool m_alive;
	NestMissile* m_missile;
	sf::CircleShape m_collisionRadius;
	void resolveCollisions(Player *p);
	void fireProjectile();

	const int MAX_PREDATORS = 3; //maximum number of predators that can be spawned 
	int m_health = 4; //number of hits the nest can take before being destroyed
};


#endif