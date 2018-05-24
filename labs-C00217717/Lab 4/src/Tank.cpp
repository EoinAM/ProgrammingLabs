	#include "Tank.h"

double const Tank::DEG_TO_RAD = thor::Pi / 180.0f;


Tank::Tank(sf::Texture const & texture, sf::Vector2f const & pos, KeyHandler const & t_keyHandler)
	: m_texture(texture),m_keyHandler(t_keyHandler)
{
	
	initSprites(pos);
}

void Tank::update(double dt)
{	

	handleKeyInput();
	float baseXPos = m_tankBase.getPosition().x + std::cos(m_rotation * DEG_TO_RAD) * m_speed * (dt / 1000);
	float baseYPos = m_tankBase.getPosition().y + std::sin(m_rotation * DEG_TO_RAD) * m_speed * (dt / 1000);

	float turretXPos = m_turret.getPosition().x + std::cos(m_rotation* DEG_TO_RAD) * m_speed * (dt / 1000);
	float turretYPos = m_turret.getPosition().y + std::sin(m_rotation* DEG_TO_RAD) * m_speed * (dt / 1000);

	m_turret.setRotation(m_turretRotation);
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
	if (m_speed < 50)
	{
		m_speed += 0.25;
	}
}

void Tank::decreaseSpeed()
{
	if (m_speed > -50)
	{
		m_speed -= 0.25;
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

void Tank::increaseTurretRotation()
{
	m_turretRotation += 0.5;
	if (m_turretRotation == 360)
	{
		m_turretRotation = 0;
	}
}

void Tank::decreaseTurretRotation()
{
	m_turretRotation -= 0.5;
	if (m_turretRotation == 0)
	{
		m_turretRotation = 359;
	}
}

void Tank::handleKeyInput()
{
	if(m_keyHandler.isPressed(sf::Keyboard::Up))
	{
		increaseSpeed();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Down))
	{
		decreaseSpeed();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Right))
	{
		increaseRotation();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Left))
	{
		DecreaseRotation();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Z))
	{
		increaseTurretRotation();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::X))
	{
		decreaseTurretRotation();
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