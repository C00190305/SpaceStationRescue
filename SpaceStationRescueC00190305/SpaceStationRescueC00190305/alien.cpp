#include "alien.h"
#include <iostream>
Alien::Alien()
{

}

Alien::Alien(float maxSpeed) : m_maxSpeed(maxSpeed)
{
	m_pos = sf::Vector2f(800.0f, 300.0f);
	m_texture.loadFromFile("alienSprite.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_font.loadFromFile("college.ttf");
	m_label.setFont(m_font);
	m_label.setString(m_name);
	m_label.setScale(0.5, 0.5);
	
	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	m_radius = sf::CircleShape(RADIUS);
	m_radius.setOrigin(m_radius.getGlobalBounds().width / 2, m_radius.getGlobalBounds().height / 2);
	m_radius.setFillColor(sf::Color(255, 0, 0, 64));

	m_speed = 0.0f;
	m_sprite.setScale(0.15f, 0.15f);
	m_velocity = sf::Vector2f(0.0f, 0.0f);
}

void Alien::update(sf::RenderWindow &window, sf::Vector2f playerPosition)
{
	checkBounds(window);

	//seek(playerPosition);
	arrive(playerPosition);
	avoidCollision(playerPosition);

	if (m_seeking == true)
	{
		m_pos.x += seek(playerPosition).x;
		m_pos.y += seek(playerPosition).y;
	}

	if (m_seeking == false)
	{
		m_pos.x -= seek(playerPosition).x;
		m_pos.y -= seek(playerPosition).y;
	}

	m_sprite.setPosition(m_pos);
	m_radius.setPosition(m_sprite.getPosition());
	m_label.setPosition(sf::Vector2f(m_pos.x + 20, m_pos.y - 20));
}

void Alien::draw(sf::RenderWindow &window)
{
	window.draw(m_sprite);
	window.draw(m_radius);
	window.draw(m_label);
}

void Alien::checkBounds(sf::RenderWindow &window)
{
	if (m_sprite.getPosition().y > window.getSize().y)
	{
		m_pos.y = 0 - m_sprite.getGlobalBounds().height;
	}

	if (m_sprite.getPosition().x > window.getSize().x)
	{
		m_pos.x = 0 - m_sprite.getGlobalBounds().width;
	}

	if (m_sprite.getPosition().x < 0)
	{
		m_pos.x = window.getSize().x;
	}

	if (m_sprite.getPosition().y < 0)
	{
		m_pos.y = window.getSize().y;
	}
}

sf::Vector2f Alien::normalize(sf::Vector2f v)
{
	v.x = v.x / (sqrt((v.x * v.x) + (v.y * v.y)));
	v.y = v.y / (sqrt((v.x * v.x) + (v.y * v.y)));
	return v;
}

//Returns the vector for a seek behavior
sf::Vector2f Alien::seek(sf::Vector2f targetPosition)
{

	if (getDistance(m_pos, targetPosition) > ARRIVAL_DISTANCE)
	{
		m_arriving = false;
	}

	if (m_pos != targetPosition)
	{
		if (m_arriving == false)
		{
			if (m_speed < m_maxSpeed)
			{
				m_speed += 0.1f;
			}

			else
			{
				m_speed = m_maxSpeed;
			}
		}

	}

	if (m_pos == targetPosition)
	{
		m_speed = 0;
	}

	m_direction.x = targetPosition.x - m_pos.x; //get direction
	m_direction.y = targetPosition.y - m_pos.y;

	m_sprite.setRotation((atan2f(m_direction.y, m_direction.x) *  (180 / 3.14159)) + 90); //note, Y comes first in atan2f

	//normalize(m_direction);
	m_direction = normalize(m_direction);

	m_velocity.x = m_direction.x * m_speed; //get velocity vector based on direction and speed
	m_velocity.y = m_direction.y * m_speed;

	return m_velocity;
}

void Alien::arrive(sf::Vector2f targetPosition)
{
	if (getDistance(m_pos, targetPosition) < ARRIVAL_DISTANCE)
	{
		m_arriving = true;
	}


	if (m_arriving == true)
	{
		if (m_speed > MIN_SPEED)
		{
			m_speed -= 0.1f;
		}

		else
		{
			m_speed = 0;
		}
	}

}

void Alien::avoidCollision(sf::Vector2f targetPosition)
{
	if (thor::length(m_pos - targetPosition) < RADIUS)
	{
		//acos returns the inverse cosine, * 180/PI for degrees
		if (thor::signedAngle(m_velocity + m_pos, targetPosition) * (180.0f / 3.14159f) < fovAngle)
		{
			if (m_seeking == true)
			{
				m_seekClock.restart();
				m_seeking = false;
			}
		}
	}

	if (m_seeking == false)
	{
		m_seekTimer = m_seekClock.getElapsedTime();
		if (m_seekTimer.asMilliseconds() > 1000)
		{
			m_seeking = true;
		}
	}
}

float Alien::getDistance(sf::Vector2f v1, sf::Vector2f v2)
{
	return sqrtf((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));
}