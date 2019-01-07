#pragma once
#ifndef PREDATOR_H
#define PREDATOR_H

#include "SFML/Graphics.hpp"
#include "Thor/Math.hpp"
#include "Thor/Vectors.hpp"
#include <iostream>

class Predator
{
public:
	Predator();
	void update(sf::RenderWindow &window, sf::Vector2f targetPosition, sf::Vector2f targetVelocity);
	void draw(sf::RenderWindow &window);
private:

	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_pos;
	sf::Vector2f m_velocity;
	sf::Vector2f m_direction;
	sf::Vector2f m_pursuitPosition;
	float m_speed;

	sf::Text m_label;
	sf::String m_name = "Predator";
	sf::Font m_font;

	sf::Time m_pursueTimer;
	sf::Clock m_pursueClock;

	sf::CircleShape m_cone;

	sf::CircleShape m_radius;

	const int RADIUS = 120;
	float fovAngle = 90.0f;

	bool m_pursuing = true;


	//returns a vector from the behavior
	sf::Vector2f pursue(sf::Vector2f targetPosition, sf::Vector2f targetVelocity);
	void avoidCollision(sf::Vector2f targetPosition);
	void checkBounds(sf::RenderWindow &window);
	sf::Vector2f normalize(sf::Vector2f v);
};


#endif // !PURSUITALIEN_H

