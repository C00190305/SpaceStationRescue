#include "AlienNest.h"

AlienNest::AlienNest()
{

}

AlienNest::AlienNest(sf::Vector2f position) : m_pos(position)
{
	m_texture.loadFromFile("nest.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);
}

void AlienNest::update()
{
	//decide time between spawns
	//check max isnt met yet
	//spawn new alien
	//check collision between nest and player projectile
}

void AlienNest::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}