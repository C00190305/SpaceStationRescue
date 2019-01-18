#include "NPCManager.h"

NPCManager::NPCManager()
{

}
//Initialize containers for each type of enemy entity in the game
NPCManager::NPCManager(tmx::Map* map) : m_mapRef(map)
{
	//Nests
	m_alienNestVector.push_back(new AlienNest(sf::Vector2f((58 * TILE_WIDTH) - 70, (5 * TILE_HEIGHT) - 60)));
	m_alienNestVector.push_back(new AlienNest(sf::Vector2f((78 * TILE_WIDTH) - 70, (38 * TILE_HEIGHT) - 60)));
	m_alienNestVector.push_back(new AlienNest(sf::Vector2f((13 * TILE_WIDTH) - 70, (73 * TILE_HEIGHT) - 60)));

	//Worker bots with initial positions
	m_workerVector.push_back(new Worker(sf::Vector2f(6 * TILE_WIDTH, 34 * TILE_WIDTH)));
	m_workerVector.push_back(new Worker(sf::Vector2f(6 * TILE_WIDTH, 41 * TILE_WIDTH)));
	m_workerVector.push_back(new Worker(sf::Vector2f(20 * TILE_WIDTH, 34 * TILE_WIDTH)));
	m_workerVector.push_back(new Worker(sf::Vector2f(20 * TILE_WIDTH, 41 * TILE_WIDTH)));
	m_workerVector.push_back(new Worker(sf::Vector2f(39 * TILE_WIDTH, 46 * TILE_WIDTH)));
	m_workerVector.push_back(new Worker(sf::Vector2f(55 * TILE_WIDTH, 39 * TILE_WIDTH)));
	m_workerVector.push_back(new Worker(sf::Vector2f(36 * TILE_WIDTH, 7 * TILE_WIDTH)));
	m_workerVector.push_back(new Worker(sf::Vector2f(61 * TILE_WIDTH, 43 * TILE_WIDTH)));
	m_workerVector.push_back(new Worker(sf::Vector2f(44 * TILE_WIDTH, 66 * TILE_WIDTH)));
	m_workerVector.push_back(new Worker(sf::Vector2f(58 * TILE_WIDTH, 81 * TILE_WIDTH)));
	m_workerVector.push_back(new Worker(sf::Vector2f(75 * TILE_WIDTH, 12 * TILE_WIDTH)));
	m_workerVector.push_back(new Worker(sf::Vector2f(80 * TILE_WIDTH, 60 * TILE_WIDTH)));
	m_workerVector.push_back(new Worker(sf::Vector2f(86 * TILE_WIDTH, 30 * TILE_WIDTH)));
	m_workerVector.push_back(new Worker(sf::Vector2f(13 * TILE_WIDTH, 67 * TILE_WIDTH)));
	m_workerVector.push_back(new Worker(sf::Vector2f(23 * TILE_WIDTH, 73 * TILE_WIDTH)));
	m_workerVector.push_back(new Worker(sf::Vector2f(38 * TILE_WIDTH, 73 * TILE_WIDTH)));
	m_workerVector.push_back(new Worker(sf::Vector2f(60 * TILE_WIDTH, 66 * TILE_WIDTH)));
}

//Update
//@param p: Player object
void NPCManager::updateEntities(Player* p)
{
	int workerVectorSize = m_workerVector.size();
	for (int i = 0; i < workerVectorSize; i++)
	{
		m_workerVector.at(i)->update();
	}

	int nestVectorSize = m_alienNestVector.size();
	for (int i = 0; i < nestVectorSize; i++)
	{
		m_alienNestVector.at(i)->update(p, m_workerVector);
	}

	resolveCollisions(p);
}

//Render entities
void NPCManager::drawEntities(sf::RenderWindow &window)
{
	int nestVectorSize = m_alienNestVector.size();
	for (int i = 0; i < nestVectorSize; i++)
	{
		m_alienNestVector.at(i)->draw(window);
	}

	int workerVectorSize = m_workerVector.size();
	for (int i = 0; i < workerVectorSize; i++)
	{
		m_workerVector.at(i)->draw(window);
	}
}

//NPC Collision detection method
void NPCManager::resolveCollisions(Player* p)
{
	//Check collision between player and worker bots
	int workerVectorSize = m_workerVector.size();
	for (int i = 0; i < workerVectorSize; i++)
	{
		if (m_workerVector.at(i)->getSprite().getGlobalBounds().intersects(p->getSprite().getGlobalBounds()))
		{
			m_workerVector.erase(m_workerVector.begin() + i);
			p->addScore(1);
			break;
		}
	}

	//Check and resolve collisions between nest missiles and players
	int nestVectorSize = m_alienNestVector.size();
	for (int i = 0; i < nestVectorSize; i++)
	{
		if (m_alienNestVector.at(i)->getMissile()->getSprite().getGlobalBounds().intersects(p->getSprite().getGlobalBounds()))
		{
			m_alienNestVector.at(i)->getMissile()->collisionDetected();
			p->reduceHealth(15);
			break;
		}

		//Check and resolve collisions between nests and player projectiles
		int playerBulletVectorSize = p->getProjectileManager().getProjectilePool().size();
		for (int j = 0; j < playerBulletVectorSize; j++)
		{
			if (m_alienNestVector.at(i)->getCollisionRadius().getGlobalBounds().intersects(p->getProjectileManager().getProjectilePool().at(j)->getSprite().getGlobalBounds()))
			{
				m_alienNestVector.at(i)->reduceHealth(1);
				p->getProjectileManager().getProjectilePool().at(j)->collisionDetected();
				break;
			}
		}

		//If the nest is dead, remove it from memory
		if (m_alienNestVector.at(i)->isAlive() == false)
		{
			m_alienNestVector.erase(m_alienNestVector.begin() + i);
			break;
		}
	}
}

std::vector<Worker*> NPCManager::getWorkers()
{
	return m_workerVector;
}

std::vector<AlienNest*> NPCManager::getNests()
{
	return m_alienNestVector;
}