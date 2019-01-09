#include "AlienNest.h"

AlienNest::AlienNest()
{

}

AlienNest::AlienNest(sf::Vector2f position) : m_pos(position)
{
	m_texture.loadFromFile("nest.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);
	m_alive = true;
}

void AlienNest::update()
{
	if (m_health <= 0)
	{
		m_alive == false;
	}

	if (m_alive == true)
	{
		//update things
		//decide time between spawns
		//check max isnt met yet
		//spawn new alien
		//check collision between nest and player projectile
	}

}

void AlienNest::draw(sf::RenderWindow& window)
{
	if (m_alive == true)
	{
		window.draw(m_sprite);
	}
}

bool AlienNest::isAlive()
{
	return m_alive;
}