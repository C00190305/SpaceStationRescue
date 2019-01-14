#include "HUD.h"

//Default constructor
HUD::HUD(Level level)
{
	m_minimapPosition = sf::Vector2f(1500, 1500); //position the minimap
	m_minimapTexture.create(2900, 3000); //2900, 3000 the size of the world
	
	//Get each layer and draw it to the rendertexture to be used as a minimap
	for (int i = 0; i < level.getDrawableLayers().size(); i++)
	{
		//level.getDrawableLayers() returns a std::vector of MapLayer pointers.
		m_minimapTexture.draw(*level.getDrawableLayers().at(i));
	}

	m_minimapSprite.setTexture(m_minimapTexture.getTexture());
	m_minimapTexture.setSmooth(true);

	//Generating a mipmap gets rid of line aliasing when scaling the texture down
	m_minimapTexture.generateMipmap();
	m_minimapSprite.setPosition(m_minimapPosition);
	m_minimapSprite.setScale(0.05f, -0.05f);

	m_minimapRect = sf::RectangleShape(sf::Vector2f(2900 * 0.05f, 3000 * 0.05f));
	m_minimapRect.setFillColor(sf::Color(0, 0, 0, 128));
	m_minimapRect.setScale(1.0f, -1.0f); // flip to match the scale change on the RenderTexture
}

//Update method for HUD components
//@param offsetPosition: position to offset the drawing of the HUD
void HUD::update(sf::Vector2f offsetPosition)
{
	int offsetX = 250;
	int offsetY = 75;
	m_minimapSprite.setPosition(sf::Vector2f(offsetPosition.x + offsetX, offsetPosition.y - offsetY));
	m_minimapRect.setPosition(sf::Vector2f(offsetPosition.x + offsetX, offsetPosition.y - offsetY));
}

//Render method
//@param window: reference to an sf::RenderWindow object
void HUD::draw(sf::RenderWindow &window)
{
	window.draw(m_minimapRect);
	window.draw(m_minimapSprite);
}