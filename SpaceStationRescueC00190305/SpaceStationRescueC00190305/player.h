#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"
#include <iostream>

#include "ProjectileManager.h"

class Player
{
public:
	Player();
	void update(sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	void setVelocity(const sf::Vector2f& v);
	void collisionDetected();
	const sf::Sprite& getSprite();

private:
	sf::Sprite m_sprite;
	sf::Sprite m_shadowSprite;
	sf::Texture m_texture;
	sf::Texture m_shadowTexture;
	sf::Vector2f m_pos;
	sf::Vector2f m_oldPos;
	sf::Vector2f m_velocity;
	sf::Vector2f m_direction;
	sf::Mouse m_mouse;
	std::string m_collisionTag = "player";
	ProjectileManager* m_projectileManager;
	bool m_collided = false;
	float m_speed;
	int m_rotationAngle;
	int nextAngle;
	//const sf::Vector2f MAX_VELOCITY = sf::Vector2f(5.0f, 5.0f);
	const float MAX_VELOCITY = 8.0f;

	void move();
	float getNewOrientation(float currentOrientation, sf::Vector2f currentVelocity);
	void checkBounds(sf::RenderWindow &window);
	void fireProjectile();
	int normalize(sf::Vector2f v);

};
#endif // PLAYER_H
