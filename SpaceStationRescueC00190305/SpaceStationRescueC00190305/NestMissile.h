#pragma once
#ifndef NESTMISSILE_H
#define NESTMISSILE_H

#include "SFML/Graphics.hpp"

//Interceptor missile that is spawned by alien nests
class NestMissile
{
public:
	NestMissile();
	NestMissile(sf::Vector2f pos);
	void update(sf::Vector2f targetPosition, sf::Vector2f targetVelocity);
	void draw(sf::RenderWindow& window);
	bool alive();
	void init();
	void setAlive(bool alive);
	sf::Sprite getSprite();
	void collisionDetected();
private:
	void intercept(sf::Vector2f targetPosition, sf::Vector2f targetVelocity);

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_pos;
	sf::Vector2f m_spawnPos;
	sf::Vector2f m_direction;
	sf::Vector2f m_velocity;
	float m_speed = 7.5f; //Player moves at a speed of 8 but having the same velocity as the player makes these missiles way too strong
	int m_ttl = 300; //60 game ticks per second * 5 seconds = 300 ticks
	sf::Vector2f m_pursuitPosition;
	bool m_alive; //alive flag
	void normalize(sf::Vector2f& v);

	void reset();


};

#endif 
