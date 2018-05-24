/// <summary>
/// @Author Eoin Abbey-Maher
/// </summary>

#include "Enemy.h"

/// <summary>
/// Default constructor
/// </summary>
Enemy::Enemy()
{
}

/// <summary>
/// Default Destructor
/// </summary>
Enemy::~Enemy()
{
}

void Enemy::update(float t_moveSpeed)
{
	move(t_moveSpeed);
}

void Enemy::render(sf::RenderWindow & t_window)
{
	if (m_isShown)
	{
		t_window.draw(m_body);
	}
}

/// <summary>
/// Function to move the enemy 
/// 
/// WHen the enemy hits one of the sides of the screen the boolean is set to True
/// This is then checked in the Game.cpp and allows us to swap the direction of all Enemies
/// 
/// position of the enemy is updated here also
/// </summary>
/// <param name="t_speed"></param>
void Enemy::move(float t_speed)
{
	m_position.x += t_speed;
	if ((m_position.x >= ScreenSize::s_width - 60 || m_position.x <= 10) && m_isShown)
	{
		m_dirSwap = true;
	}
	m_body.setPosition(m_position);
}





