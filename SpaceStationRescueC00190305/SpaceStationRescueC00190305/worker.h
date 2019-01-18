#ifndef WORKER_H
#define WORKER_H

#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Thor/Math.hpp"
#include "Thor/Vectors.hpp"
#include "AnimatedSprite.hpp"
#include "Animation.hpp"


class Worker
{
public:
	Worker();
	Worker(sf::Vector2f position);
	void update();
	void draw(sf::RenderWindow &window);
	AnimatedSprite getSprite();
	void collisionDetected();
	sf::Vector2f getPosition();
private:
	AnimatedSprite m_sprite;
	Animation m_walkAnimation;
	sf::Texture m_texture;
	sf::Vector2f m_pos;
	sf::Vector2f m_oldPos;
	sf::Vector2f m_velocity;
	sf::Vector2f m_direction;

	sf::Vector2f m_newPos;
	float m_speed = 0.4f;

	sf::CircleShape m_radius;
	const int RADIUS = 120;
	float fovAngle = 90.0f;
	bool m_wandering = true;
	bool m_collected = false;
	float m_rotationAngle;

	sf::Time m_wanderTimer;
	sf::Clock m_wanderClock;

	sf::Vector2f normalize(sf::Vector2f v);
	//Wander behavior
	sf::Vector2f wander();
	float getDistance(sf::Vector2f v1, sf::Vector2f v2);

};

#endif // !WORKER_H