#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"
#include <iostream>


class Player
{
public:
	Player();
	void update(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	const sf::Sprite& getSprite();

private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_pos;
	sf::Vector2f m_velocity;
	sf::Vector2f m_direction;
	sf::Mouse m_mouse;
	float m_speed;
	int m_rotationAngle;
	int nextAngle;
	//const sf::Vector2f MAX_VELOCITY = sf::Vector2f(5.0f, 5.0f);
	const float MAX_VELOCITY = 15.0f;

	void move();
	float getNewOrientation(float currentOrientation, sf::Vector2f currentVelocity);
	void checkBounds(sf::RenderWindow &window);
	int normalize(sf::Vector2f v);

};
#endif // PLAYER_H
