#include "Projectile.h"

double const Projectile::DEG_TO_RAD = thor::Pi / 180.0f;

////////////////////////////////////////////////////////////
void Projectile::init(sf::Texture const & texture, double x, double y, double rotation)
{	
	m_projectile.setTexture(texture);
	m_projectile.setTextureRect(m_projectileRect);
	m_projectile.setOrigin(m_projectileRect.width / 2.0, m_projectileRect.height / 2.0);
	m_projectile.setPosition(x, y);
	
	m_projectile.setRotation(rotation); 
	m_speed = s_MAX_SPEED;
}

////////////////////////////////////////////////////////////

bool Projectile::update(double dt, std::vector<sf::Sprite>& wallSprites, sf::Sprite & t_Aitank)
{
	if (!inUse())
	{
		// If this projectile is not in use, there is no update routine to perform.
		return false;
	}

	sf::Vector2f position = m_projectile.getPosition();
	sf::Vector2f newPos(position.x + std::cos(DEG_TO_RAD  * m_projectile.getRotation()) * m_speed * (dt / 1000),
		position.y + std::sin(DEG_TO_RAD  * m_projectile.getRotation()) * m_speed * (dt / 1000));

	m_projectile.setPosition(newPos.x, newPos.y);

	if (!isOnScreen(newPos))
	{
		m_speed = 0;
	}
	else
	{
		// Still on-screen, have we collided with a wall?
		for (sf::Sprite const & sprite : wallSprites)
		{
			// Checks if the projectile has collided with the current wall sprite.
			if (CollisionDetector::collision(m_projectile, sprite))
			{
				m_speed = 0;
			}
		}
		if (CollisionDetector::collision(m_projectile, t_Aitank))
		{
			m_speed = 0;
			tankCollision = true;
		}
	}
	return m_speed == s_MAX_SPEED;
}

////////////////////////////////////////////////////////////
bool Projectile::inUse() const 
{ 
	// Projectile is not in use if not moving.
	return m_speed == s_MAX_SPEED; 
}

////////////////////////////////////////////////////////////
bool Projectile::isOnScreen(sf::Vector2f position) const
{	
	return position.x - m_projectileRect.width / 2 > 0.f
		&& position.x + m_projectileRect.width / 2 < ScreenSize::s_width
		&& position.y - m_projectileRect.height / 2 > 0.f
		&& position.y + m_projectileRect.height / 2 < ScreenSize::s_height;
}