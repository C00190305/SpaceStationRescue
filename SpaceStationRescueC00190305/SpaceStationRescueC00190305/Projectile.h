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
	void setAlive(bool alive);
	void collisionDetected();
	bool checkDead();
	void setTimeToLive(int ttl);
	void resetPosition();

	//initialization of movement.
	void init(sf::Vector2f direction, sf::Vector2f pos, const int angle);
	sf::Sprite getSprite();
	bool inUse();

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_pos;
	sf::Vector2f m_initialPos;
	sf::Vector2f m_direction;
	int m_angle;
	const int MAX_BULLET_POOL = 20;
	float velocity;
	bool m_inUse;
	bool m_alive;
	
	int m_ttl = 310;
	void normalize(sf::Vector2f &v);
};
#endif // !PROJECTILE_H
