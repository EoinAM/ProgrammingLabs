	#include "Tank.h"

double const Tank::DEG_TO_RAD = thor::Pi / 180.0f;

Tank::Tank(sf::Texture const & texture, std::vector<sf::Sprite> & m_wallSprites,  sf::Vector2f const & pos, KeyHandler const & t_keyHandler)
	: m_texture(texture),m_keyHandler(t_keyHandler), m_wallSprites(m_wallSprites)
{
	initSprites(pos);
}

void Tank::update(double dt)
{	
	m_pool.update(dt, m_wallSprites);

	if (checkWallCollisions())
	{
		deflect();
	}

	handleKeyInput();
	
	float baseXPos = m_tankBase.getPosition().x + std::cos(m_rotation * DEG_TO_RAD) * m_speed * (dt / 1000);
	float baseYPos = m_tankBase.getPosition().y + std::sin(m_rotation * DEG_TO_RAD) * m_speed * (dt / 1000);

	float turretXPos = m_turret.getPosition().x + std::cos(m_rotation* DEG_TO_RAD) * m_speed * (dt / 1000);
	float turretYPos = m_turret.getPosition().y + std::sin(m_rotation* DEG_TO_RAD) * m_speed * (dt / 1000);

	m_turret.setRotation(m_turretRotation);
	m_tankBase.setRotation(m_rotation);

	m_tankBase.setPosition(baseXPos, baseYPos);
	m_turret.setPosition(turretXPos, turretYPos);

	m_previousPosition = m_tankBase.getPosition();

	if (m_fireRequested && m_shootTimer > 0)
	{
		m_shootTimer -= dt;
	}
	else
	{
		m_shootTimer = 1100;
		m_fireRequested = false;
	}
}

void Tank::render(sf::RenderWindow & window) 
{
	window.draw(m_tankBase);
	window.draw(m_turret);
	m_pool.render(window);
}

void Tank::increaseSpeed()
{
	if (m_speed < 100)
	{
		m_speed += 1;
	}
}

void Tank::decreaseSpeed()
{
	if (m_speed > -100)
	{
		m_speed -= 1;
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

sf::Vector2f Tank::getPosition()
{
	return m_tankBase.getPosition();
}

void Tank::requestFire()
{
	m_fireRequested = true;
	if (m_shootTimer == s_TIME_BETWEEN_SHOTS)
	{
		sf::Vector2f tipOfTurret(m_turret.getPosition().x + 2.0f, m_turret.getPosition().y);
		tipOfTurret.x += std::cos(DEG_TO_RAD * m_turret.getRotation()) *((m_turret.getLocalBounds().top + m_turret.getLocalBounds().height) * 1.7f);
		tipOfTurret.y += std::sin(DEG_TO_RAD  * m_turret.getRotation()) * ((m_turret.getLocalBounds().top + m_turret.getLocalBounds().height) * 1.7f);
		m_pool.create(m_texture, tipOfTurret.x, tipOfTurret.y, m_turret.getRotation());
	}
}

void Tank::deflect()
{
	adjustRotation();

	if (m_speed != 0)
	{
		m_enableRotation = false;
		m_tankBase.setPosition(m_previousPosition);
		m_turret.setPosition(m_previousPosition);

		if (m_previousSpeed < 0)
		{
			m_speed = 8;
		}
		else
		{
			m_speed = -8;
		}
	}
}

void Tank::adjustRotation()
{
	if (m_rotation != m_previousRotation)
	{
		if (m_rotation > m_previousRotation)
		{
			m_rotation = m_previousRotation - 1;
		}
		else
		{
			m_rotation = m_previousRotation + 1;
		}
	}

	if (m_turretRotation != m_previousTurretRotation)
	{
		m_turretRotation = m_previousTurretRotation;
	}
}

void Tank::handleKeyInput()
{
	if(m_keyHandler.isPressed(sf::Keyboard::Up))
	{
		m_previousSpeed = m_speed;
		increaseSpeed();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Down))
	{
		m_previousSpeed = m_speed;
		decreaseSpeed();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Right))
	{
		m_previousRotation = m_rotation;
		increaseRotation();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Left))
	{
		m_previousRotation = m_rotation;
		DecreaseRotation();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Z))
	{
		m_previousTurretRotation = m_turretRotation;
		increaseTurretRotation();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::X))
	{
		m_previousTurretRotation = m_turretRotation;
		decreaseTurretRotation();
	}
	if (m_keyHandler.isPressed(sf::Keyboard::Space))
	{
		requestFire();
	}
}



bool Tank::checkWallCollisions()
{
	for (sf::Sprite const & sprite : m_wallSprites)
	{
		if (CollisionDetector::collision(m_turret, sprite) || CollisionDetector::collision(m_tankBase, sprite))
		{
			return true;
		}
	}
	return false;
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