#include "EnemyManager.h"

EnemyManager::EnemyManager()
{

}

EnemyManager::EnemyManager(tmx::Map* map) : m_mapRef(map)
{
	m_alienNestVector.push_back(new AlienNest(sf::Vector2f((58 * TILE_WIDTH) - 70, (5 * TILE_HEIGHT) - 60)));
	m_alienNestVector.push_back(new AlienNest(sf::Vector2f((78 * TILE_WIDTH) - 70, (38 * TILE_HEIGHT) - 60)));
	m_alienNestVector.push_back(new AlienNest(sf::Vector2f((13 * TILE_WIDTH) - 70, (73 * TILE_HEIGHT) - 60)));
}

void EnemyManager::updateEntities()
{

}

void EnemyManager::drawEntities(sf::RenderWindow &window)
{
	for (int i = 0; i < MAX_NESTS; i++)
	{
		m_alienNestVector.at(i)->draw(window);
	}
}