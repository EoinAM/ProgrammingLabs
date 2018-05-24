#include "PickUp.h"



PickUp::PickUp()
{
	srand(time(NULL));

	m_sprite.setPosition(m_position);
	m_sprite.setScale(.25, .25);
	m_healthTexture.loadFromFile("./resources/images/healthpack.png");
	m_sprite.setTexture(m_healthTexture);

	m_detectionCircle.setRadius(600);
	m_detectionCircle.setOrigin(m_detectionCircle.getRadius(), m_detectionCircle.getRadius());
	m_detectionCircle.setPosition(m_position);
	spawn();
}


PickUp::~PickUp()
{
}

void PickUp::update(double t_deltaTime)
{

	if (isDrawn)
	{
		if (m_aliveTimer <= 0)
		{
			isDrawn = false;
			m_isAvailable = false;
			m_spawnTimer -= t_deltaTime;
		}
		else
		{
			m_aliveTimer -= t_deltaTime;
		}

		if (m_spawnTimer <= 0)
		{
			spawn();
		}
	}
	
	m_sprite.setPosition(m_position);
	m_detectionCircle.setPosition(m_position);
}

void PickUp::render(sf::RenderWindow & t_window)
{
	if (isDrawn && m_isAvailable)
	{
		t_window.draw(m_sprite);
	}
}

void PickUp::spawn()
{
	m_position.x = std::rand() % (500) + 100;
	m_position.y = std::rand() % (500) + 100;

	m_sprite.setPosition(m_position);
	m_detectionCircle.setPosition(m_position);

	m_isAvailable = true;

	m_spawnTimer = 20000;
	m_aliveTimer = 18000;
}

sf::Sprite PickUp::getBody()
{
	return m_sprite;
}

sf::Vector2f PickUp::getPosition()
{
	return m_position;
}

bool PickUp::intersectsCircle(sf::Sprite t_tank)
{
	float distanceBetween;
	distanceBetween = sqrt(((t_tank.getPosition().x - m_detectionCircle.getPosition().x) * (t_tank.getPosition().x - m_detectionCircle.getPosition().x) +
		(t_tank.getPosition().y - m_detectionCircle.getPosition().y) * (t_tank.getPosition().y - m_detectionCircle.getPosition().y)));

	if (distanceBetween <= m_detectionCircle.getRadius())
	{
		return true;
	}
	else
	{
		return false;
	}
}

