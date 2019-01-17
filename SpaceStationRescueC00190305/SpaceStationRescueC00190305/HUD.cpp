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

	m_infoRect = sf::RectangleShape(sf::Vector2f(2900 * 0.05f, 3000 * 0.02f));
	m_infoRect.setFillColor(sf::Color(0, 0, 0, 128));

	m_font.loadFromFile("college.ttf");
	m_scoreText.setFont(m_font);
	m_scoreText.setCharacterSize(12);
	m_scoreText.setStyle(sf::Text::Style::Bold);

	m_healthText.setFont(m_font);
	m_healthText.setCharacterSize(12);
	m_healthText.setStyle(sf::Text::Style::Bold);
	m_healthText.setFillColor(sf::Color::Cyan);

	m_numNestsText.setFont(m_font);
	m_numNestsText.setCharacterSize(12);
	m_numNestsText.setStyle(sf::Text::Style::Bold);
	m_numNestsText.setFillColor(sf::Color::Red);
}

//Update method for HUD components
//@param offsetPosition: position to offset the drawing of the HUD
void HUD::update(sf::Vector2f offsetPosition, int playerScore, int playerHealth, int numNests)
{
	int mapOffsetX = 250;
	int mapOffsetY = 75;
	m_minimapSprite.setPosition(sf::Vector2f(offsetPosition.x + mapOffsetX, offsetPosition.y - mapOffsetY));
	m_minimapRect.setPosition(sf::Vector2f(offsetPosition.x + mapOffsetX, offsetPosition.y - mapOffsetY));
	m_minimapRect.setOutlineThickness(1.0f);
	m_minimapRect.setOutlineColor(sf::Color::White);
	
	m_scoreString = "Workers Rescued: " + std::to_string(playerScore);
	m_scoreText.setString(m_scoreString);
	m_scoreText.setPosition(sf::Vector2f(offsetPosition.x + mapOffsetX, offsetPosition.y - mapOffsetY + 25));

	m_healthString = "Shields: " + std::to_string(playerHealth);
	m_healthText.setString(m_healthString);
	m_healthText.setPosition(sf::Vector2f(offsetPosition.x + mapOffsetX, offsetPosition.y - mapOffsetY + 40));

	m_numNestsString = "Nests: " + std::to_string(numNests);
	m_numNestsText.setString(m_numNestsString);
	m_numNestsText.setPosition(sf::Vector2f(offsetPosition.x + mapOffsetX, offsetPosition.y - mapOffsetY + 55));

	if (playerScore == 17) //If all worker bots have been rescued
	{
		m_scoreText.setString("MISSION COMPLETE");
		m_scoreText.setFillColor(sf::Color::Green);
	}
	
	m_infoRect.setPosition(sf::Vector2f(offsetPosition.x + mapOffsetX, offsetPosition.y - mapOffsetY + 25));
	m_infoRect.setOutlineThickness(1.0f);
	m_infoRect.setOutlineColor(sf::Color::White);
}

//Render method
//@param window: reference to an sf::RenderWindow object
void HUD::draw(sf::RenderWindow &window)
{
	window.draw(m_minimapRect);
	window.draw(m_infoRect);
	window.draw(m_minimapSprite);
	window.draw(m_scoreText);
	window.draw(m_healthText);
	window.draw(m_numNestsText);
}