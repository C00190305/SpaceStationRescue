#include "ProjectileManager.h"

ProjectileManager::ProjectileManager()
{

}
//Overloaded constructor
//@params: pos sf::vector2f
ProjectileManager::ProjectileManager(sf::Vector2f pos) : m_pos(pos)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		m_projectiles.push_back(new Projectile());
	}
}

void ProjectileManager::update()
{
	int size = m_projectiles.size();
	for (int i = 0; i < size; i++)
	{
		m_projectiles.at(i)->update();
	}
}

void ProjectileManager::draw(sf::RenderWindow &window)
{
	int size = m_projectiles.size();
	for (int i = 0; i < size; i++)
	{
		m_projectiles.at(i)->draw(window);
	}
}

//Called to create a new projectile object by adding it to the vector
//direction: sf::Vector2f initial direction vector
//pos: sf::Vector2f initial position of the projectile
//angle: int angle to rotate the sprite to
void ProjectileManager::create(sf::Vector2f direction, sf::Vector2f pos, const int angle)
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		if (m_projectiles.at(i)->alive() == false)
		{
			m_projectiles.at(i)->init(direction, pos, angle);
			std::cout << "Firing proj number: " << i << std::endl;
			break;
		}
	}
}