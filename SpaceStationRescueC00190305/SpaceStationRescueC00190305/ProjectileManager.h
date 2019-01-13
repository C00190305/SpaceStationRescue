#pragma once
#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include "SFML/Graphics.hpp"
#include "Projectile.h"

#include <vector>
#include <iostream>

//Responsible for managing pools of projectiles
class ProjectileManager
{
public:
	ProjectileManager();
	ProjectileManager(sf::Vector2f pos);
	void update();
	void create(sf::Vector2f direction, sf::Vector2f pos, const int angle);
	void draw(sf::RenderWindow& window);
private:
	sf::Vector2f m_pos;
	std::vector<Projectile*> m_projectiles;
	const int MAX_PROJECTILES = 20;
};

#endif

