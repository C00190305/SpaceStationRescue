#pragma once
#include "SFML/Graphics.hpp"
#include "Level.h"

class HUD
{
public:
	HUD(Level level);
	~HUD();
	void update(sf::Vector2f offsetPosition);
	void draw(sf::RenderWindow& window);
private:
	sf::RenderTexture m_minimapTexture;
	sf::Sprite m_minimapSprite;
	sf::Vector2f m_minimapPosition;
	std::vector<MapLayer*> m_drawableLayers; //A container for MapLayer objects to draw to the rendertexture
	sf::RectangleShape m_minimapRect; //Transparent rectangle to make the minimap stand out.
};
