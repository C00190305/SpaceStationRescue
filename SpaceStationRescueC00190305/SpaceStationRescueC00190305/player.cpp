
#include "player.h"

//Default constructor
Player::Player()
{
	m_pos = sf::Vector2f(80 * 32, 67 * 32);
	m_texture.loadFromFile("player.png");
	m_shadowTexture.loadFromFile("shadowSprite.png");
	m_texture.setSmooth(true);
	m_shadowTexture.setSmooth(true);
	m_texture.generateMipmap();
	m_sprite.setTexture(m_texture);
	m_shadowSprite.setTexture(m_shadowTexture);
	m_shadowSprite.setColor(sf::Color(0, 0, 0, 200));
	m_sprite.setPosition(m_pos);
	m_shadowSprite.setPosition(sf::Vector2f(m_pos.x + 10, m_pos.y + 10));
	m_rotationAngle = 0;
	m_speed = 0;
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_shadowSprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(0.02f, 0.02f);
	m_shadowSprite.setScale(0.02f, 0.02f);
	m_sprite.setRotation(m_rotationAngle);
	m_velocity = sf::Vector2f(0.0f, 0.0f);

	m_projectileManager = new ProjectileManager(m_pos);
	m_score = 0;
	m_health = 100;
}

//Update function to be called in the main update loop
void Player::update(sf::RenderWindow &window)
{
	move();
	m_projectileManager->update();
	fireProjectile();
	//checkBounds(window);
}

//Render function
//@param: sf::Renderwindow
void Player::draw(sf::RenderWindow &window)
{
	window.draw(m_shadowSprite);
	m_projectileManager->draw(window);
	window.draw(m_sprite);
}

//Function responsible for using the keys to manipulate the player object
void Player::move()
{
	const float PI = 3.14159;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		if (m_speed < MAX_VELOCITY)
		{
			m_speed += 0.5f;
		}

		else
		{
			m_speed = MAX_VELOCITY;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		if (m_speed > -MAX_VELOCITY)
		{
			m_speed -= 0.5f;
		}

		else
		{
			m_speed = -MAX_VELOCITY;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		m_rotationAngle -= 4;
		m_sprite.setRotation(m_rotationAngle);
		m_shadowSprite.setRotation(m_rotationAngle);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		m_rotationAngle += 4;
		m_sprite.setRotation(m_rotationAngle);
		m_shadowSprite.setRotation(m_rotationAngle);
	}

	m_direction.x = (sin(m_rotationAngle * PI / 180)); //in radians
	m_direction.y = (-cos(m_rotationAngle * PI / 180)); //in radians

	normalize(m_direction);

	m_velocity.x = m_direction.x * m_speed; //find velocity
	m_velocity.y = m_direction.y * m_speed;

	m_oldPos = m_pos; //store current position before moving to the new position

	
	m_pos.x += m_velocity.x; //increment the position by the velocity
	m_pos.y += m_velocity.y;


	m_sprite.setPosition(m_pos); //set position
	m_shadowSprite.setPosition(sf::Vector2f(m_pos.x + 4, m_pos.y + 4));
	
}

void Player::fireProjectile()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{ 
		m_shootTimer = m_shootClock.getElapsedTime();
		if (m_shootTimer.asMilliseconds() > m_shootDelay)
		{
			//m_projectileVector.push_back(new Projectile(m_direction, m_pos, m_angle));
			m_projectileManager->create(m_direction, m_pos, m_rotationAngle);
			m_shootTimer = m_shootClock.restart();
		}
	}
}

//Vector normalization function
int Player::normalize(sf::Vector2f v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y)));
	
}

int Player::getHealth()
{
	return m_health;
}

void Player::reduceHealth(int amount)
{
	m_health -= amount;
}

//Returns position as sf::vector2f
sf::Vector2f Player::getPosition()
{
	return m_pos;
}

//Returns velocity as sf::vector2f
sf::Vector2f Player::getVelocity()
{
	return m_velocity;
}

int Player::getScore()
{
	return m_score;
}

void Player::addScore(int amount)
{
	m_score += amount;
}

//Returns reference to sprite
const sf::Sprite& Player::getSprite()
{
	return m_sprite;
}

//Method to be called when a collision is detected with another game object
//Resets position and sets speed to be 0.
void Player::collisionDetected()
{
	m_pos.x = m_oldPos.x;
	m_pos.y = m_oldPos.y;
		
	m_speed = 0;
}

ProjectileManager Player::getProjectileManager()
{
	return *m_projectileManager;
}

//Velocity setter
void Player::setVelocity(const sf::Vector2f& v)
{
	m_velocity = v;
}