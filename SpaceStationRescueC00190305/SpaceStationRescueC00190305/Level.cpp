#include "Level.h"

Level::Level()
{

}

Level::Level(std::string path)
{
	m_map = new tmx::Map;
	m_map->load(path);
	layerOne = new MapLayer(*m_map, 1);
}

void Level::draw(sf::RenderWindow &window)
{
	for (auto &layer : m_map->getLayers())
	{
		window.draw(layer);
	}
}