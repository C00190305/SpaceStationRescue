#pragma once
#ifndef SWEEPER_H
#define SWEEPER_H

#include "SFML/Graphics.hpp"
#include "Thor/Math.hpp"
#include "Thor/Vectors.hpp"

#include "worker.h"


class Sweeper
{
public:
	Sweeper();
	Sweeper(sf::Vector2f spawnPosition);
	void update(Worker* worker);
	void draw(sf::RenderWindow &window);
	int getWorkersCaptured();
	void capturedWorker();
	void wallCollisionDetected();

	sf::Sprite getSprite();

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_pos;
	sf::Vector2f m_velocity;
	sf::Vector2f m_direction;

	int m_workersCaptured;

	float m_speed;

	sf::CircleShape m_detectionRadius;

	float m_rotationAngle;

	bool m_seeking;

	//returns the vector for seek behavior.
	sf::Vector2f seek(sf::Vector2f targetPosition);
	sf::Vector2f wander();

	sf::Vector2f normalize(sf::Vector2f v);

};
#endif // TRIANGLE_H
