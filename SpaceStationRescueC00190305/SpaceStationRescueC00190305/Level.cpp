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
	if (layerOne->getGlobalBounds().intersects(p->getSprite().getGlobalBounds()))
	{
		std::cout << "wall collision" << std::endl;
	}
}

tmx::Map* Level::getMap()
{
	return m_map;
}