#include "Worker.h"

Worker::Worker()
{
	m_pos = sf::Vector2f(1300.0f, 1000.0f);

	//Set up animation
	m_texture.loadFromFile("workerBot.png");
	m_walkAnimation.setSpriteSheet(m_texture);
	m_walkAnimation.addFrame(sf::IntRect(0, 32, 16, 16));
	m_walkAnimation.addFrame(sf::IntRect(32, 32, 16, 16));
	m_walkAnimation.addFrame(sf::IntRect(64, 32, 16, 16));
	m_walkAnimation.addFrame(sf::IntRect(96, 32, 16, 16));
	m_walkAnimation.addFrame(sf::IntRect(128, 32, 16, 16));
	m_walkAnimation.addFrame(sf::IntRect(160, 32, 16, 16));
	m_sprite.setAnimation(m_walkAnimation); //set the AnimatedSprite's animation to be the walk animation
	m_sprite.setLooped(true);

	m_sprite.setPosition(m_pos);
	m_newPos = sf::Vector2f(100, 100);

	m_sprite.setScale(1.2f, 1.2f);

	
	m_radius = sf::CircleShape(RADIUS);
	m_radius.setOrigin(m_radius.getGlobalBounds().width / 2, m_radius.getGlobalBounds().height / 2);
	m_radius.setFillColor(sf::Color(255, 0, 0, 64));

	m_velocity = sf::Vector2f(0.0f, 0.0f);

	//Flag for if this bot has been collected by a sweeper or player
	m_collected = false; 
	
}

void Worker::update()
{

	m_sprite.play();
	m_sprite.update(sf::milliseconds(17));
	m_sprite.setPosition(m_pos);

	m_radius.setPosition(m_sprite.getPosition());
}

void Worker::draw(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}




//Returns a vector for wander behavior
sf::Vector2f Worker::wander(sf::RenderWindow &window)
{
	if (getDistance(m_pos, m_newPos) > 20) //if we havent reached the target
	{
		m_speed = 2.0f;
	}

	if (getDistance(m_pos, m_newPos) < 20) //else get a new target to go towards
	{
		getNewTarget(window);
	}

	m_direction.x = m_newPos.x - m_pos.x; //get direction
	m_direction.y = m_newPos.y - m_pos.y;

	m_sprite.setRotation((atan2f(m_direction.y, m_direction.x) *  (180 / 3.14159)) + 90); //note, Y comes first in atan2f

	m_direction = normalize(m_direction);

	m_velocity.x = m_direction.x * m_speed; //get velocity vector based on direction and speed
	m_velocity.y = m_direction.y * m_speed;

	return m_velocity;

}

//sets the m_newPos vector to a new random position
void Worker::getNewTarget(sf::RenderWindow &window)
{
	m_newPos.x = thor::random(0.0f, static_cast<float>(window.getSize().x));
	m_newPos.y = thor::random(0.0f, static_cast<float>(window.getSize().y));
	
}

//normalize vector
sf::Vector2f Worker::normalize(sf::Vector2f v)
{
	v.x = v.x / (sqrt((v.x * v.x) + (v.y * v.y)));
	v.y = v.y / (sqrt((v.x * v.x) + (v.y * v.y)));
	return v;
}

//distance between 2 vectors
float Worker::getDistance(sf::Vector2f v1, sf::Vector2f v2)
{
	return sqrtf((v1.x - v2.x)*(v1.x - v2.x) + (v1.y - v2.y)*(v1.y - v2.y));
}