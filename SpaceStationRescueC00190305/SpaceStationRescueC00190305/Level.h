#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include "SFML/Graphics.hpp"
#include "tmxlite/Config.hpp"
#include "tmxlite/Map.hpp"
#include "SFMLOrthogonalLayer.hpp"
#include <vector>


class Level
{
public:
	Level();
	Level(std::string path);
	void draw(sf::RenderWindow &window);
private:
	std::string m_path;
	tmx::Map* m_map;
	MapLayer* layerOne;
	MapLayer* layerTwo;
	MapLayer* layerThree;
};


#endif