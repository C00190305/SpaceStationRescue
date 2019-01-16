#include "Worker.h"

Worker::Worker()
{

}

//Overloaded constructor
//@params position: sf::vector2f of the initial position
Worker::Worker(sf::Vector2f	position) : m_pos(position)
{
	

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
	m_oldPos = m_pos;
	m_newPos = sf::Vector2f(100, 100);

	m_sprite.setScale(1.2f, 1.2f);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);

	m_rotationAngle = thor::random(0.0f, 360.0f);
	
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
	
	//Make sprite face the direction it is walking in
	//by flipping scale in the X plane
	if (m_rotationAngle > 180)
	{
		m_sprite.setScale(-1.2f, 1.2f);
	}

	else
	{
		m_sprite.setScale(1.2f, 1.2f);
	}

	//Get the previous position of the entity before it moves to be used in wall collision resolution
	m_oldPos = m_pos;

	m_pos += wander();

	m_sprite.setPosition(m_pos);

}

void Worker::draw(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}




//Returns a vector for wander behavior
sf::Vector2f Worker::wander()
{
	float PI = 3.14159;

	//Calculate new angle to walk toward
	m_rotationAngle += thor::random(-15.0f, 15.0f);

	m_direction.x = (sin(m_rotationAngle * PI / 180)); //in radians
	m_direction.y = (-cos(m_rotationAngle * PI / 180)); //in radians

	

	m_direction = normalize(m_direction);

	m_velocity.x = m_direction.x * m_speed; //get velocity vector based on direction and speed
	m_velocity.y = m_direction.y * m_speed;

	return m_velocity;

}

//For collision detection with level walls
void Worker::collisionDetected()
{
	m_pos = m_oldPos;
	m_rotationAngle = m_rotationAngle * -1.0f;
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

AnimatedSprite Worker::getSprite()
{
	return m_sprite;
}