	#include "Tank.h"

double const Tank::DEG_TO_RAD = thor::Pi / 180.0f;

Tank::Tank(sf::Texture const & texture, sf::Vector2f const & pos)
: m_texture(texture)
{
	
	initSprites(pos);
}

void Tank::update(double dt)
{	
	float baseXPos = m_tankBase.getPosition().x + std::cos(m_rotation * DEG_TO_RAD) * m_speed * (dt / 1000);
	float baseYPos = m_tankBase.getPosition().y + std::sin(m_rotation * DEG_TO_RAD) * m_speed * (dt / 1000);

	float turretXPos = m_turret.getPosition().x + std::cos(m_rotation * DEG_TO_RAD) * m_speed * (dt / 1000);
	float turretYPos = m_turret.getPosition().y + std::sin(m_rotation * DEG_TO_RAD) * m_speed * (dt / 1000);

	m_turret.setRotation(m_rotation);
	m_tankBase.setRotation(m_rotation);

	m_tankBase.setPosition(baseXPos, baseYPos);
	m_turret.setPosition(turretXPos, turretYPos);
}

void Tank::render(sf::RenderWindow & window) 
{
	window.draw(m_tankBase);
	window.draw(m_turret);
}

void Tank::increaseSpeed()
{
	if (m_speed < 100)
	{
		m_speed += 0.5;
	}
}

void Tank::decreaseSpeed()
{
	if (m_speed > -100)
	{
		m_speed -= 0.5;
	}
}

void Tank::increaseRotation()
{
	m_rotation += 0.5;
	if (m_rotation == 360)
	{
		m_rotation = 0;
	}
}

void Tank::DecreaseRotation()
{

	m_rotation -= 0.5;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;	
	}
}


void Tank::initSprites(sf::Vector2f const & pos)
{
	// Initialise the tank base
	m_tankBase.setTexture(m_texture);
	sf::IntRect baseRect(2, 43, 79, 43);
	m_tankBase.setTextureRect(baseRect);
	m_tankBase.setOrigin(baseRect.width / 2.0, baseRect.height / 2.0);
	m_tankBase.setPosition(pos);

	// Initialise the turret
	m_turret.setTexture(m_texture);
	sf::IntRect turretRect(19, 1, 83, 31);
	m_turret.setTextureRect(turretRect);
	m_turret.setOrigin(turretRect.width / 3.0, turretRect.height / 2.0);
	m_turret.setPosition(pos);

}