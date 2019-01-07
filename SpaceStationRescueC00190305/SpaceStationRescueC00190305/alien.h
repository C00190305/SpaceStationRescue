#pragma once
#ifndef ALIEN_H
#define ALIEN_H

#include "SFML/Graphics.hpp"
#include "Thor/Math.hpp"
#include "Thor/Vectors.hpp"


class Alien
{
public:
	Alien();
	Alien(float maxSpeed);
	void update(sf::RenderWindow &window, sf::Vector2f playerPosition);
	void draw(sf::RenderWindow &window);

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_pos;
	sf::Vector2f m_velocity;
	sf::Vector2f m_direction;

	sf::Text m_label;
	sf::String m_name = "Seek and Arrive";
	sf::Font m_font;

	float m_maxSpeed;
	const float MIN_SPEED = 0.5f;
	float m_speed;
	sf::Vector2f normalize(sf::Vector2f v);
	bool m_arriving = false;
	
	sf::Time m_seekTimer;
	sf::Clock m_seekClock;

	sf::CircleShape m_radius;
	const int RADIUS = 120;
	float fovAngle = 90.0f;

	bool m_seeking = true;

	const float ARRIVAL_DISTANCE = 120.0f;

	void checkBounds(sf::RenderWindow &window);
	void arrive(sf::Vector2f targetPosition);

	//returns the vector for seek behavior.
	sf::Vector2f seek(sf::Vector2f targetPosition);
	void avoidCollision(sf::Vector2f targetPosition);
	float getDistance(sf::Vector2f v1, sf::Vector2f v2);

};
#endif // TRIANGLE_H
