#include "AlienNest.h"

AlienNest::AlienNest()
{

}

AlienNest::AlienNest(sf::Vector2f position) : m_pos(position)
{
	m_texture.loadFromFile("nest.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);
	m_missile = new NestMissile(sf::Vector2f(m_pos.x + m_sprite.getLocalBounds().width / 2, m_pos.y + m_sprite.getLocalBounds().height));
	m_detectionRadius = sf::CircleShape(250.0f);
	m_collisionRadius = sf::CircleShape(60.0f);
	m_detectionRadius.setOrigin(m_detectionRadius.getLocalBounds().width / 2, m_detectionRadius.getLocalBounds().height / 2);
	m_detectionRadius.setPosition(sf::Vector2f(m_pos.x + m_sprite.getLocalBounds().width / 2, m_pos.y + m_sprite.getLocalBounds().height / 2));
	m_collisionRadius.setOrigin(m_collisionRadius.getLocalBounds().width / 2, m_collisionRadius.getLocalBounds().height / 2);
	m_collisionRadius.setPosition(sf::Vector2f(m_pos.x + m_sprite.getLocalBounds().width / 2, m_pos.y + m_sprite.getLocalBounds().height / 2));
	m_alive = true;
	
}

void AlienNest::update(Player* p)
{
	if (m_health <= 0)
	{
		m_alive = false;
	}

	if (m_alive == true)
	{
		//update things
		//decide time between spawns
		//check max isnt met yet
		//spawn new alien
		//check collision between nest and player projectile
		m_missile->update(p->getPosition(), p->getVelocity());
		resolveCollisions(p);
	}

}

void AlienNest::draw(sf::RenderWindow& window)
{
	if (m_alive == true)
	{
		window.draw(m_sprite);
		m_missile->draw(window);
	}
}

void AlienNest::fireProjectile()
{

	m_shootTimer = m_shootClock.getElapsedTime();
	if (m_shootTimer.asMilliseconds() > m_shootDelay)
	{
		if (m_missile->alive() == false)
		{
			m_missile->init();
		}
		m_shootTimer = m_shootClock.restart();
	}
}

void AlienNest::resolveCollisions(Player* p)
{
	if (m_detectionRadius.getGlobalBounds().intersects(p->getSprite().getGlobalBounds()))
	{
		fireProjectile();
	}
}

bool AlienNest::isAlive()
{
	return m_alive;
}

NestMissile* AlienNest::getMissile()
{
	return m_missile;
}

void AlienNest::reduceHealth(int amount)
{
	m_health -= amount;
}

sf::CircleShape AlienNest::getCollisionRadius()
{
	return m_collisionRadius;
}

sf::Sprite AlienNest::getSprite()
{
	return m_sprite;
}