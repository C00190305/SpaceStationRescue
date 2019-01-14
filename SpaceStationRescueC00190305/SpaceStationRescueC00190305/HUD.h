#pragma once
#include "SFML/Graphics.hpp"

class HUD
{
public:
	HUD();
	~HUD();
	void update();
	void draw(sf::RenderWindow& window);
private:
};
