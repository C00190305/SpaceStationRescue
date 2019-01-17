#pragma once
#include "SFML/Graphics.hpp"
#include "Level.h"

class HUD
{
public:
	HUD(Level level);
	~HUD();
	void update(sf::Vector2f offsetPosition, int playerScore, int playerHealth);
	void draw(sf::RenderWindow& window);
private:
	sf::RenderTexture m_minimapTexture;
	sf::Sprite m_minimapSprite;
	sf::Vector2f m_minimapPosition;
	std::vector<MapLayer*> m_drawableLayers; //A container for MapLayer objects to draw to the rendertexture
	sf::RectangleShape m_minimapRect; //Transparent rectangle to make the minimap stand out.
	sf::RectangleShape m_infoRect; //Transparent rectangle to make game information stand out.

	sf::Font m_font;
	std::string m_scoreString;
	std::string m_healthString;
	sf::Text m_scoreText;
	sf::Text m_healthText;
};
