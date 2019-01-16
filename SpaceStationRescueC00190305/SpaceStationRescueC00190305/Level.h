#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include "SFML/Graphics.hpp"
#include "tmxlite/Config.hpp"
#include "tmxlite/Map.hpp"
#include "SFMLOrthogonalLayer.hpp"
#include "NPCManager.h"
#include "player.h"
#include <vector>
#include <iostream>

class Level
{
public:
	Level();
	Level(std::string path);
	void update(Player* p, ProjectileManager projectileManager, NPCManager npcManager);
	void draw(sf::RenderWindow &window);
	tmx::Map* getMap();
	std::vector<MapLayer*> getDrawableLayers();
private:
	sf::Sprite m_backgroundSprite;
	sf::Texture m_backgroundTexture;
	std::string m_path;
	tmx::Map* m_map;
	MapLayer* layerOne;
	MapLayer* layerTwo;
	MapLayer* layerThree;
	std::vector<tmx::Object> m_objects;
	std::vector<MapLayer*> m_drawableLayers;
	
	void resolveCollisions(Player* p, ProjectileManager projectileManager, NPCManager npcManager);
};


#endif