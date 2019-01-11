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

void Level::update(Player* p)
{
	resolveCollisions(p);
}

void Level::draw(sf::RenderWindow &window)
{
	window.draw(m_backgroundSprite);
	window.draw(*layerOne);
	window.draw(*layerTwo);
}

void Level::resolveCollisions(Player* p)
{
	for (const auto& collisionObject : m_objects)
	{
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

	}
}

tmx::Map* Level::getMap()
{
	return m_map;
}
