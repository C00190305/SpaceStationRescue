#include "Sweeper.h"
#include <iostream>
Sweeper::Sweeper()
{

}

//@param spawnPosition: initial position where the sweeper will be spawned by the nest
Sweeper::Sweeper(sf::Vector2f spawnPosition) : m_pos(spawnPosition)
{
	m_texture.loadFromFile("sweeper.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_pos);

	m_speed = 0.04f;
	m_sprite.setScale(0.10f, 0.10f);
	m_sprite.setOrigin(sf::Vector2f(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2));
	m_velocity = sf::Vector2f(0.0f, 0.0f);
	m_rotationAngle = thor::random(0.0f, 360.0f);

	//Radius to detect worker bots
	m_detectionRadius = sf::CircleShape(100.0f);
	m_detectionRadius.setOrigin(sf::Vector2f(m_detectionRadius.getLocalBounds().width / 2, m_detectionRadius.getLocalBounds().height / 2));
	m_detectionRadius.setPosition(sf::Vector2f(m_pos.x + m_sprite.getLocalBounds().width / 2-  30, m_pos.y + m_sprite.getLocalBounds().height / 2 - 30));
	m_seeking = false;

	m_workersCaptured = 0;

	m_font.loadFromFile("college.ttf");
	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::Yellow);
	m_text.setCharacterSize(14);
	m_text.setOutlineThickness(0.5f);
	m_text.setOutlineColor(sf::Color::Black);
	
}

//Update method
//@param targetPosition: position of the entity to seek
void Sweeper::update(Worker* worker)
{

	if (m_detectionRadius.getGlobalBounds().intersects(worker->getSprite().getGlobalBounds()))
	{
		m_seeking = true;
	}

	else
	{
		m_seeking = false;
	}

	if (m_rotationAngle > 180)
	{
		m_sprite.setScale(-0.10f, 0.10f);
	}

	else
	{
		m_sprite.setScale(0.10f, 0.10f);
	}

	if (m_seeking == true)
	{
		m_speed = 0.1f; //increase speed
		m_pos += seek(worker->getPosition());
	}

	if (m_seeking == false)
	{
		m_speed = 0.04f; //put speed back to original value
		m_pos += wander();
	}

	m_text.setString(std::to_string(m_workersCaptured));

	m_text.setPosition(m_pos.x + 20, m_pos.y - 15);
	m_detectionRadius.setOrigin(sf::Vector2f(m_detectionRadius.getLocalBounds().width / 2, m_detectionRadius.getLocalBounds().height / 2));
	m_detectionRadius.setPosition(sf::Vector2f(m_pos.x + m_sprite.getGlobalBounds().width / 2 - 15, m_pos.y + m_sprite.getGlobalBounds().height / 2 - 15));
	m_sprite.setPosition(m_pos);
}

void Sweeper::draw(sf::RenderWindow &window)
{
	window.draw(m_sprite);
	window.draw(m_text);
}

sf::Vector2f Sweeper::normalize(sf::Vector2f v)
{
	v.x = v.x / (sqrt((v.x * v.x) + (v.y * v.y)));
	v.y = v.y / (sqrt((v.x * v.x) + (v.y * v.y)));
	return v;
}

//Returns the vector for a seek behavior
sf::Vector2f Sweeper::seek(sf::Vector2f targetPosition)
{


	m_direction.x = targetPosition.x - m_pos.x; //get direction
	m_direction.y = targetPosition.y - m_pos.y;

	m_direction = normalize(m_direction);

	m_velocity.x = m_direction.x * m_speed; //get velocity vector based on direction and speed
	m_velocity.y = m_direction.y * m_speed;

	return m_velocity;
}

sf::Vector2f Sweeper::wander()
{
	float PI = 3.14159;

	//Calculate new angle to walk toward
	m_rotationAngle += thor::random(-2.0f, 2.0f);

	m_direction.x = (sin(m_rotationAngle * PI / 180)); //in radians
	m_direction.y = (-cos(m_rotationAngle * PI / 180)); //in radians

	m_direction = normalize(m_direction);

	m_velocity.x = m_direction.x * m_speed; //get velocity vector based on direction and speed
	m_velocity.y = m_direction.y * m_speed;

	return m_velocity;
}

void Sweeper::wallCollisionDetected()
{
	m_rotationAngle += 180.0f;
}

void Sweeper::capturedWorker()
{
	m_workersCaptured++;
}

sf::Sprite Sweeper::getSprite()
{
	return m_sprite;
}

int Sweeper::getWorkersCaptured()
{
	return m_workersCaptured;
}

void Sweeper::setCapturedWorkers(int val)
{
	m_workersCaptured = val;
}

