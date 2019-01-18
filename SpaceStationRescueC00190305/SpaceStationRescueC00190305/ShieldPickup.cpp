#include "ShieldPickup.h"

ShieldPickup::ShieldPickup()
{

}

//Overloaded constructor
//@param pos: sf::vector2f of the position to place the pickup
ShieldPickup::ShieldPickup(sf::Vector2f pos) : m_pos(pos)
{
	m_texture.loadFromFile("shieldPickup.png");
	m_texture.generateMipmap();
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);
	m_sprite.setScale(0.1f, 0.1f);
}

void ShieldPickup::replace(sf::Vector2f newPos)
{
	m_pos = newPos;
	m_sprite.setPosition(m_pos);
}

sf::Sprite ShieldPickup::getSprite()
{
	return m_sprite;
}

void ShieldPickup::draw(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}