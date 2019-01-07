#include "Predator.h"

Predator::Predator()
{
	m_pos = sf::Vector2f(1000.0f, 360.0f);
	m_texture.loadFromFile("predator.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_speed = 2.0f;

	m_font.loadFromFile("college.ttf");
	m_label.setFont(m_font);
	m_label.setString(m_name);
	m_label.setScale(0.5, 0.5);

	m_sprite.setScale(0.10f, 0.10f);
	m_velocity = sf::Vector2f(0.0f, 0.0f);

	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);

	m_cone = sf::CircleShape(80, 3);
	m_radius = sf::CircleShape(120);
	m_radius.setFillColor(sf::Color(255, 0, 0, 64));
	m_cone.setOrigin(sf::Vector2f(m_cone.getPoint(3).x, m_cone.getPoint(3).y));
	m_radius.setOrigin(m_radius.getGlobalBounds().width / 2, m_radius.getGlobalBounds().height / 2);
}

void Predator::update(sf::RenderWindow &window, sf::Vector2f targetPosition, sf::Vector2f targetVelocity)
{
	checkBounds(window);
	//pursue(targetPosition, targetVelocity);
	
	avoidCollision(targetPosition);
	
	if (m_pursuing == true)
	{
		m_pos.x += pursue(targetPosition, targetVelocity).x;
		m_pos.y += pursue(targetPosition, targetVelocity).y;
	}

	if (m_pursuing == false)
	{
		m_pos.x -= pursue(targetPosition, targetVelocity).x;
		m_pos.y -= pursue(targetPosition, targetVelocity).y;
	}

	m_sprite.setPosition(m_pos);
	//m_cone.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y));
	m_radius.setPosition(m_sprite.getPosition());
	m_label.setPosition(sf::Vector2f(m_pos.x + 20, m_pos.y - 15));
	
}

void Predator::draw(sf::RenderWindow &window)
{
	window.draw(m_sprite);
	//window.draw(m_cone);
	window.draw(m_radius);
	window.draw(m_label);
}


	//method for checking the bounding window to wrap around
void Predator::checkBounds(sf::RenderWindow &window)
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

sf::Vector2f Predator::pursue(sf::Vector2f targetPosition, sf::Vector2f targetVelocity)
{
	int futureTicks = 60; //60 updates per second, so it will calulcate where it will be in 1 second.
	
	m_pursuitPosition.x = targetPosition.x + targetVelocity.x * futureTicks;
	m_pursuitPosition.y = targetPosition.y + targetVelocity.y * futureTicks;

	m_direction.x = m_pursuitPosition.x - m_pos.x; //get direction
	m_direction.y = m_pursuitPosition.y - m_pos.y;

	m_sprite.setRotation((atan2f(m_direction.y, m_direction.x) *  (180 / 3.14159)) + 90); //note, Y comes first in atan2f
	m_cone.setRotation((atan2f(m_direction.y, m_direction.x) *  (180 / 3.14159)) - 90);

	m_direction = normalize(m_direction);


	m_velocity.x = m_direction.x * m_speed; //get velocity vector based on direction and speed
	m_velocity.y = m_direction.y * m_speed;

	return m_velocity;
}


void Predator::avoidCollision(sf::Vector2f targetPosition)
{
	if (thor::length(m_pos - targetPosition) < RADIUS)
	{
		//acos returns the inverse cosine, * 180/PI for degrees
		if (thor::signedAngle(m_velocity + m_pos, targetPosition) * (180.0f / 3.14159f) < fovAngle)
		{
			if (m_pursuing == true)
			{
				m_pursueClock.restart();
				m_pursuing = false;
			}
		}
	}

	if (m_pursuing == false)
	{
		m_pursueTimer = m_pursueClock.getElapsedTime();
		if (m_pursueTimer.asMilliseconds() > 1000)
		{
			m_pursuing = true;
		}
	}
}

//normalize vector
sf::Vector2f Predator::normalize(sf::Vector2f v)
{
	v.x = v.x / (sqrt((v.x * v.x) + (v.y * v.y)));
	v.y = v.y / (sqrt((v.x * v.x) + (v.y * v.y)));
	return v;
}


