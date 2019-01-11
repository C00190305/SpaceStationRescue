#include "Projectile.h"

/////////////////////////////////////////////////////////////
//Default constructor
//
//
/////////////////////////////////////////////////////////////
Projectile::Projectile()
{

}


/////////////////////////////////////////////////////////////
// default constructor sets up all initial values.
//	@param direction: sf::vector2f initial direction vector
//  @param pos: sf::Vector2f initial position
//	@param angle: const int initial angle to set sprite 
/////////////////////////////////////////////////////////////
Projectile::Projectile(sf::Vector2f direction, sf::Vector2f pos, const int angle) : m_direction(direction), m_pos(pos), m_angle(angle)
{
	m_texture.loadFromFile("playerProjectile.png");
	m_sprite.setTexture(m_texture);
	
	m_sprite.setScale(1.0f, 1.0f);
	velocity = 0.8f;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setPosition(sf::Vector2f(m_pos.x - 5, m_pos.y));
	m_sprite.setRotation(angle);
	normalize(m_direction);
	
	m_alive = true;
}

/////////////////////////////////////////////////////////////
//checks if it has been used by the pool and updates accordingly
//
//
/////////////////////////////////////////////////////////////
void Projectile::update()
{
	if (m_alive == true)
	{
		m_pos += m_direction * velocity;
		m_sprite.setPosition(m_pos);

		m_ttl -= 1;
	}

	if (m_ttl <= 0)
	{
		m_alive = false;
	}
}

/////////////////////////////////////////////////////////////
//
//
//
/////////////////////////////////////////////////////////////
void Projectile::init(sf::Vector2f direction, sf::Vector2f pos, const int angle)
{
	m_inUse = true;

	m_direction = direction;
	normalize(m_direction);

	m_pos = pos;
	m_angle = angle;
	m_sprite.setRotation(m_angle + 90);
}

/////////////////////////////////////////////////////////////
//draw method
//
//
/////////////////////////////////////////////////////////////
void Projectile::draw(sf::RenderWindow &window)
{
	if (m_alive == true)
	{
		window.draw(m_sprite);
	}
}

/////////////////////////////////////////////////////////////
//Normalizes the vector for use in the movement calculation
//
//
/////////////////////////////////////////////////////////////
void Projectile::normalize(sf::Vector2f &v)
{
	float length = sqrtf((v.x * v.x) + (v.y * v.y));
	if (length != 0)
	{
		v = sf::Vector2f(v.x / length, v.y / length);
	}
}

bool Projectile::alive()
{
	return m_alive;
}

bool Projectile::checkDead()
{
	if (m_alive == false)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool Projectile::inUse()
{
	return m_inUse;
}

Projectile::~Projectile()
{

}