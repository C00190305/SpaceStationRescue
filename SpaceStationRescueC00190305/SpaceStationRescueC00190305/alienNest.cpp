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
//Update method
//@param p: player object
void AlienNest::update(Player* p, std::vector<Worker*> workerVector)
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
		spawnSweeper();
		resolveCollisions(p);
		updateSweepers(workerVector);
	}

}

void AlienNest::draw(sf::RenderWindow& window)
{
	if (m_alive == true)
	{
		m_missile->draw(window);
		window.draw(m_sprite);
		for (int i = 0; i < m_sweepers.size(); i++)
		{
			m_sweepers.at(i)->draw(window);
		}
	}
}

//Function that resolves collisions between workers and sweepers
//@param workerVector: a std::vector of pointers to worker objects.
void AlienNest::updateSweepers(std::vector<Worker*> workerVector)
{
	for (int i = 0; i < workerVector.size(); i++)
	{
		for (int j = 0; j < m_sweepers.size(); j++)
		{
			m_sweepers.at(j)->update(workerVector.at(i));
			if (workerVector.at(i)->getSprite().getGlobalBounds().intersects(m_sweepers.at(j)->getSprite().getGlobalBounds()))
			{
				workerVector.erase(workerVector.begin() + i);
				m_sweepers.at(j)->capturedWorker();
			}
		}
	}
}
//Fires a projectile is one is available and the timer allows.
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

//Spawns a new sweeper if the timer allows and the maximum hasn't been spawned yet.
void AlienNest::spawnSweeper()
{
	m_spawnTimer = m_spawnClock.getElapsedTime();
	if (m_spawnTimer.asMilliseconds() > m_spawnDelay)
	{
		if (m_sweepers.size() <= MAX_SWEEPERS)
		{
			m_sweepers.push_back(new Sweeper(sf::Vector2f(m_pos.x + m_sprite.getLocalBounds().width / 2, m_pos.y + m_sprite.getLocalBounds().height / 2)));
			m_spawnTimer = m_spawnClock.restart();
		}
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

std::vector<Sweeper*> AlienNest::getSweepers()
{
	return m_sweepers;
}