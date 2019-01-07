#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "Thor/Math.hpp"
#include "Thor/Vectors.hpp"


class Worker
{

public:
	Worker();
	void update(sf::RenderWindow &window, sf::Vector2f targetPosition, sf::Vector2f targetVelocity);
	void draw(sf::RenderWindow &window);
private:
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Vector2f m_pos;
	sf::Vector2f m_velocity;
	sf::Vector2f m_direction;
	sf::Text m_label;
	sf::String m_name = "Worker";
	sf::Font m_font;

	sf::Vector2f m_newPos;
	float m_speed = 10.0f;

	sf::CircleShape m_radius;
	const int RADIUS = 120;
	float fovAngle = 90.0f;
	bool m_wandering = true;

	sf::Time m_wanderTimer;
	sf::Clock m_wanderClock;

	sf::Vector2f normalize(sf::Vector2f v);
	void checkBounds(sf::RenderWindow &window);
	//Wander behavior
	sf::Vector2f wander(sf::RenderWindow &window);
	void getNewTarget(sf::RenderWindow &window);
	float getDistance(sf::Vector2f v1, sf::Vector2f v2);
	void avoidCollision(sf::Vector2f targetPosition, sf::Vector2f targetVelocity);

};