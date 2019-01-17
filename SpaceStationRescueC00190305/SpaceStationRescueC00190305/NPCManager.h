#ifndef NPCMANAGER_H
#define NPCMANAGER_H

#include "tmxlite/Config.hpp"
#include "tmxlite/Map.hpp"
#include "tmxlite/Object.hpp"
#include "tmxlite/ObjectGroup.hpp"

#include "SFML/Graphics.hpp"
#include "AlienNest.h"
#include "worker.h"

#include <vector>

///Class for managing collections of different enemy entities in the game
class NPCManager
{
public:
	NPCManager();
	NPCManager(tmx::Map* map);
	void updateEntities(Player* p);
	void drawEntities(sf::RenderWindow &window);
	std::vector<Worker*> getWorkers();
	std::vector<AlienNest*> getNests();
private:
	std::vector<AlienNest*> m_alienNestVector;
	std::vector<Worker*> m_workerVector;
	tmx::Map* m_mapRef;
	const int MAX_NESTS = 3;
	const int TILE_WIDTH = 32;
	const int TILE_HEIGHT = 32;

	void resolveCollisions(Player* p);
};


#endif 