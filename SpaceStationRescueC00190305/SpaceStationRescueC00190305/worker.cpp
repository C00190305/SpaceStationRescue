#include "Worker.h"

Worker::Worker()
{
	m_pos = sf::Vector2f(1000.0f, 360.0f);
	m_texture.loadFromFile("worker.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);
	m_newPos = sf::Vector2f(100, 100);

	m_font.loadFromFile("college.ttf");
	m_label.setFont(m_font);
	m_label.setString(m_name);
	m_label.setScale(0.5, 0.5);

	m_sprite.setScale(0.15f, 0.15f);

	m_sprite.setOrigin(m_sprite.getTextureRect().width / 2, m_sprite.getTextureRect().height / 2);
	m_radius = sf::CircleShape(RADIUS);
	m_radius.setOrigin(m_radius.getGlobalBounds().width / 2, m_radius.getGlobalBounds().height / 2);
	m_radius.setFillColor(sf::Color(255, 0, 0, 64));

	m_velocity = sf::Vector2f(0.0f, 0.0f);
	
}

void Worker::update(sf::RenderWindow &window, sf::Vector2f targetPosition, sf::Vector2f targetVelocity)
{
	checkBounds(window);
	//wander(window);
	avoidCollision(targetPosition, targetVelocity);

	if (m_wandering == true)
	{
		m_pos.x += wander(window).x;
		m_pos.y += wander(window).y;
	}

	if (m_wandering == false)
	{
		m_pos.x -= wander(window).x;
		m_pos.y -= wander(window).y;
	}

	m_sprite.setPosition(m_pos);

	m_label.setPosition(sf::Vector2f(m_pos.x + 20, m_pos.y - 15));
	m_radius.setPosition(m_sprite.getPosition());
}

void Worker::draw(sf::RenderWindow &window)
{
	window.draw(m_sprite);
	window.draw(m_radius);
	window.draw(m_label);
}

//method for checking the bounding window to wrap around
void Worker::checkBounds(sf::RenderWindow &window)
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

//Returns a vector for wander behavior
sf::Vector2f Worker::wander(sf::RenderWindow &window)
{
	if (getDistance(m_pos, m_newPos) > 20) //if we havent reached the target
	{
		m_speed = 2.0f;
	}

	if (getDistance(m_pos, m_newPos) < 20) //else get a new target to go towards
	{
		getNewTarget(window);
	}

	m_direction.x = m_newPos.x - m_pos.x; //get direction
	m_direction.y = m_newPos.y - m_pos.y;

	m_sprite.setRotation((atan2f(m_direction.y, m_direction.x) *  (180 / 3.14159)) + 90); //note, Y comes first in atan2f

	m_direction = normalize(m_direction);

	m_velocity.x = m_direction.x * m_speed; //get velocity vector based on direction and speed
	m_velocity.y = m_direction.y * m_speed;

	return m_velocity;

}

//method that calculates the angle between 2 vectors
void Worker::avoidCollision(sf::Vector2f targetPosition, sf::Vector2f targetVelocity)
{
	if (thor::length(m_pos - targetPosition) < RADIUS)
	{
		//acos returns the inverse cosine, * 180/PI for degrees
		if(thor::signedAngle(m_velocity + m_pos, targetPosition) * (180.0f / 3.14159f) < fovAngle)
		{
			if (m_wandering == true)
			{
				m_wanderClock.restart();
				m_wandering = false;
			}
		}
	}

	if (m_wandering == false)
	{
		m_wanderTimer = m_wanderClock.getElapsedTime();
		if (m_wanderTimer.asMilliseconds() > 1000)
		{
			m_wandering = true;
		}
	}
}

//sets the m_newPos vector to a new random position
void Worker::getNewTarget(sf::RenderWindow &window)
{
	m_newPos.x = thor::random(0.0f, static_cast<float>(window.getSize().x));
	m_newPos.y = thor::random(0.0f, static_cast<float>(window.getSize().y));
	
}

//normalize vector
sf::Vector2f Worker::normalize(sf::Vector2f v)
{
	v.x = v.x / (sqrt((v.x * v.x) + (v.y * v.y)));
	v.y = v.y / (sqrt((v.x * v.x) + (v.y * v.y)));
	return v;
}

//distance between 2 vectors
float Worker::getDistance(sf::Vector2f v1, sf::Vector2f v2)
{
	return sqrtf((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));
}