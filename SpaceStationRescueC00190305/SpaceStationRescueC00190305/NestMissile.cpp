#include "NestMissile.h"

NestMissile::NestMissile()
{

}

NestMissile::NestMissile(sf::Vector2f pos) : m_pos(pos)
{
	m_texture.loadFromFile("enemyProjectile.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);
	m_sprite.setScale(2.0f, 2.0f);
	m_spawnPos = pos;
	m_alive = false;
}

void NestMissile::update(sf::Vector2f targetPosition, sf::Vector2f targetVelocity)
{
	if (m_alive == true)
	{
		intercept(targetPosition, targetVelocity);
		m_sprite.setPosition(m_pos);
		m_ttl = m_ttl - 1;
	}

	if (m_ttl <= 0)
	{
		m_alive = false;
	}


}

void NestMissile::draw(sf::RenderWindow& window)
{
	if (m_alive == true)
	{
		window.draw(m_sprite);
	}
}

void NestMissile::init()
{
	m_alive = true;
	m_ttl = 300;
}

void NestMissile::collisionDetected()
{
	reset();
	m_ttl = 0;
}

void NestMissile::reset()
{
	m_pos = m_spawnPos;
}

//Tracks the targets position in an attempt to intercept it.
void NestMissile::intercept(sf::Vector2f targetPosition, sf::Vector2f targetVelocity)
{
	int futureTicks = 30; //60 updates per second, so it will calulcate where it will be in 0.5 seconds.

	m_pursuitPosition.x = targetPosition.x + targetVelocity.x * futureTicks;
	m_pursuitPosition.y = targetPosition.y + targetVelocity.y * futureTicks;

	m_direction.x = m_pursuitPosition.x - m_pos.x; //get direction
	m_direction.y = m_pursuitPosition.y - m_pos.y;

	m_sprite.setRotation((atan2f(m_direction.y, m_direction.x) *  (180 / 3.14159)) + 90); //note, Y comes first in atan2f

	normalize(m_direction);

	m_velocity.x = m_direction.x * m_speed; //get velocity vector based on direction and speed
	m_velocity.y = m_direction.y * m_speed;

	m_pos.x += m_velocity.x;
	m_pos.y += m_velocity.y;
}

void NestMissile::normalize(sf::Vector2f &v)
{
	float length = sqrtf((v.x * v.x) + (v.y * v.y));
	if (length != 0)
	{
		v = sf::Vector2f(v.x / length, v.y / length);
	}
}

bool NestMissile::alive()
{
	return m_alive;
}

void NestMissile::setAlive(bool alive)
{
	m_alive = alive;
}

sf::Sprite NestMissile::getSprite()
{
	return m_sprite;
}