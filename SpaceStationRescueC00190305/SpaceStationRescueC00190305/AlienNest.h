#pragma once
#include "SFML/Graphics.hpp"
#include "Predator.h"

#include <vector>

#ifndef ALIENNEST_H
#define ALIENNEST_H

class AlienNest
{
public:
	AlienNest();
	AlienNest(sf::Vector2f position);

	void update();
	void draw(sf::RenderWindow &window);
private:
	sf::Vector2f m_pos;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	std::vector<Predator*> m_predators;

	const int MAX_PREDATORS = 4; //maximum number of predators that can be spawned 
	int health = 4; //number of hits the nest can take before being destroyed
};


#endif