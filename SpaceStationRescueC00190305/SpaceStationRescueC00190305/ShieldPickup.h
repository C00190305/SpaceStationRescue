#pragma once
#ifndef SHIELDPICKUP_H
#define SHIELD_PICKUP_H

#include "SFML/Graphics.hpp"

class ShieldPickup
{
public:
	ShieldPickup();
	ShieldPickup(sf::Vector2f pos);
	void replace(sf::Vector2f newPos); //function if the shield pickup gets placed out of bounds.
	void draw(sf::RenderWindow &window);
	sf::Sprite getSprite();
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_pos;
	
};

#endif