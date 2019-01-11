#pragma once
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "SFML/Graphics.hpp"
#include "Thor/Math.hpp"

class Projectile
{
public:
	Projectile();
	Projectile(sf::Vector2f direction, sf::Vector2f pos, const int angle);
	~Projectile();
	void update();
	void draw(sf::RenderWindow &window);
	bool alive();
	bool checkDead();

	//initialization of movement.
	void init(sf::Vector2f direction, sf::Vector2f pos, const int angle);
	bool inUse();

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_pos;
	sf::Vector2f m_direction;
	int m_angle;
	const int MAX_BULLET_POOL = 20;
	float velocity;
	bool m_inUse;
	bool m_alive;
	
	int m_ttl = 100;
	void normalize(sf::Vector2f &v);
};
#endif // !PROJECTILE_H
