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

	layerOne = new MapLayer(*m_map, 0);
}

void Level::draw(sf::RenderWindow &window)
{
	window.draw(*layerOne);
}