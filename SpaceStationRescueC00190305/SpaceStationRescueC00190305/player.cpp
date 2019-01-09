
#include "player.h"


Player::Player()
{
	m_pos = sf::Vector2f(3000.0f, 3000.0f);
	m_texture.loadFromFile("player.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);
	m_rotationAngle = 0;
	m_speed = 0;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(0.05f, 0.05f);
	m_sprite.setRotation(m_rotationAngle);
	m_velocity = sf::Vector2f(0.0f, 0.0f);
}

void Player::update(sf::RenderWindow &window)
{
	move();
	//checkBounds(window);
}


void Player::draw(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}

void Player::move()
{
	const float PI = 3.14159;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		if (m_speed < MAX_VELOCITY)
		{
			m_speed += 0.5f;
		}

		else
		{
			m_speed = MAX_VELOCITY;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		if (m_speed > -MAX_VELOCITY)
		{
			m_speed -= 0.5f;
		}

		else
		{
			m_speed = -MAX_VELOCITY;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		m_rotationAngle -= 3;
		m_sprite.setRotation(m_rotationAngle);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		m_rotationAngle += 3;
		m_sprite.setRotation(m_rotationAngle);
	}

	m_direction.x = (sin(m_rotationAngle * PI / 180)); //in radians
	m_direction.y = (-cos(m_rotationAngle * PI / 180)); //in radians

	normalize(m_direction);

	m_velocity.x = m_direction.x * m_speed; //find velocity
	m_velocity.y = m_direction.y * m_speed;

	m_pos.x += m_velocity.x; //increment the position by the velocity
	m_pos.y += m_velocity.y;
	
	m_sprite.setPosition(m_pos); //set position
	
}

void Player::checkBounds(sf::RenderWindow &window)
{
	if (m_sprite.getPosition().y  > window.getSize().y)
	{
		m_pos.y = 0;
	}

	else if (m_sprite.getPosition().y < 0)
	{
		m_pos.y = window.getSize().y;
	}

	else if (m_sprite.getPosition().x > window.getSize().x)
	{
		m_pos.x = 0;
	}

	else if (m_sprite.getPosition().x < 0)
	{
		m_pos.x = window.getSize().x;
	}
}

int Player::normalize(sf::Vector2f v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y)));
	
}

float Player::getNewOrientation(float currentOrientation, sf::Vector2f velocity)
{
	const float PI = 3.14159;
	float radians;
	
	if (normalize(velocity) > 0)
	{
		radians = atan2f(m_pos.x, m_pos.y);
		return radians * (180.0 / PI);
	}

	else
	{
		return currentOrientation;
	}
}

sf::Vector2f Player::getPosition()
{
	return m_pos;
}

sf::Vector2f Player::getVelocity()
{
	return m_velocity;
}

const sf::Sprite& Player::getSprite()
{
	return m_sprite;
}