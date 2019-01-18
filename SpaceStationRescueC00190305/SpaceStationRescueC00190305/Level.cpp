#include "Level.h"

Level::Level()
{

}

Level::Level(std::string path) : m_path(path)
{
	m_map = new tmx::Map;
	if (m_map->load(m_path))
	{

	}

	m_backgroundTexture.loadFromFile("background.png");
	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setPosition(sf::Vector2f(0.0f, 0.0f));
	m_backgroundSprite.setScale(1.0f, 1.5f);

	layerOne = new MapLayer(*m_map, 0);
	layerTwo = new MapLayer(*m_map, 1);

	m_drawableLayers.push_back(layerOne);
	m_drawableLayers.push_back(layerTwo);

	//Place shield pickup
	m_shieldPickup = new ShieldPickup(sf::Vector2f(thor::random(100.0f, 2880.0f), thor::random(100.0f, 2880.0f)));
	
	const auto& layers = m_map->getLayers();
	std::cout << "Map has " << layers.size() << " layers" << std::endl;
	for (const auto& layer : layers)
	{
		std::cout << "Found Layer: " << layer->getName() << std::endl;
		std::cout << "Layer Type: " << int(layer->getType()) << std::endl;

		if (layer->getType() == tmx::Layer::Type::Object)
		{
			m_objects = layer->getLayerAs<tmx::ObjectGroup>().getObjects();
			std::cout << "Found " << m_objects.size() << " objects in layer" << std::endl;

			for (const auto& object : m_objects)
			{
				std::cout << "Object " << object.getName() << std::endl;
				const auto& properties = object.getProperties();
				std::cout << "Object has " << properties.size() << " properties" << std::endl;
				for (const auto& prop : properties)
				{
					std::cout << "Found property: " << prop.getName() << std::endl;
					std::cout << "Type: " << int(prop.getType()) << std::endl;
				}
			}
		}
	}
}

void Level::update(Player* p, ProjectileManager projectileManager, NPCManager npcManager)
{
	resolveCollisions(p, projectileManager, npcManager);
}

void Level::draw(sf::RenderWindow &window)
{
	window.draw(m_backgroundSprite);
	window.draw(*layerOne);
	window.draw(*layerTwo);
	m_shieldPickup->draw(window);
}

void Level::resolveCollisions(Player* p, ProjectileManager projectileManager, NPCManager npcManager)
{
	for (const auto& collisionObject : m_objects)
	{
		//Smart pointer to free the resource after the check completes
		std::shared_ptr<sf::FloatRect> collisionRect = std::make_shared<sf::FloatRect>();
		
		collisionRect->left = collisionObject.getAABB().left;
		collisionRect->top = collisionObject.getAABB().top;
		collisionRect->width = collisionObject.getAABB().width;
		collisionRect->height = collisionObject.getAABB().height;

		if (p->getSprite().getGlobalBounds().intersects(*collisionRect))
		{
			//std::cout << "Collision detected player" << std::endl;
			p->collisionDetected();
		}

		//Place the shield pickup in a new area if it is not inside the bounds of the level
		if (m_shieldPickup->getSprite().getGlobalBounds().intersects(*collisionRect))
		{
			m_shieldPickup->replace(sf::Vector2f(thor::random(100.0f, 2880.0f), thor::random(100.0f, 2880.0)));
		}

		//If a player collides with the shield pickup, add to their health and place the pickup somewhere new.
		if (m_shieldPickup->getSprite().getGlobalBounds().intersects(p->getSprite().getGlobalBounds()))
		{
			p->addHealth(20);
			m_shieldPickup->replace(sf::Vector2f(thor::random(100.0f, 2880.0f), thor::random(100.0f, 2880.0)));
		}

		const int POOLSIZE = 20;
		for (int i = 0; i < POOLSIZE; i++)
		{
			if (projectileManager.getProjectilePool().at(i)->alive() == true)
			{
				if (projectileManager.getProjectilePool().at(i)->getSprite().getGlobalBounds().intersects(*collisionRect))
				{
           			projectileManager.getProjectilePool().at(i)->collisionDetected();
					break;
				}
				
			}
		}

		const int NUM_WORKERS = npcManager.getWorkers().size();
		for (int i = 0; i < NUM_WORKERS; i++)
		{
			if (npcManager.getWorkers().at(i)->getSprite().getGlobalBounds().intersects(*collisionRect))
			{
				npcManager.getWorkers().at(i)->collisionDetected();
				break;
			}
		}

		for (int i = 0; i < npcManager.getNests().size(); i++)
		{
			for (int j = 0; j < npcManager.getNests().at(i)->getSweepers().size(); j++)
			{
				if (npcManager.getNests().at(i)->getSweepers().at(j)->getSprite().getGlobalBounds().intersects(*collisionRect))
				{
					npcManager.getNests().at(i)->getSweepers().at(j)->wallCollisionDetected();
					break;
				}
			}
		}

	}
}

tmx::Map* Level::getMap()
{
	return m_map;
}

std::vector<MapLayer*> Level::getDrawableLayers()
{
	return m_drawableLayers;
}