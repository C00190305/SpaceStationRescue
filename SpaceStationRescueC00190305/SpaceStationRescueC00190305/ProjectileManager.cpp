#include "ProjectileManager.h"

ProjectileManager::ProjectileManager()
{

}
//Overloaded constructor
//@params: pos sf::vector2f
ProjectileManager::ProjectileManager(sf::Vector2f pos) : m_pos(pos)
{
	
}

void ProjectileManager::update()
{
	int size = m_projectiles.size();
	for (int i = 0; i < size; i++)
	{
		m_projectiles.at(i)->update();
		if (m_projectiles.at(i)->alive() == false)
		{
			
		}
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
void ProjectileManager::createProjectile(sf::Vector2f direction, sf::Vector2f pos, const int angle)
{
	m_projectiles.push_back(new Projectile(direction, pos, angle));
}