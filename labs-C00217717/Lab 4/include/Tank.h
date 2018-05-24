#pragma once
#include <SFML/Graphics.hpp>
#include "KeyHandler.h"

#include <Thor\Math.hpp>
/// <summary>
/// @brief A simple tank controller.
/// 
/// This class will manage all tank movement and rotations.
/// </summary>


class Tank
{
public:	
	Tank(sf::Texture const & texture, sf::Vector2f const & pos, KeyHandler const & t_keyHandler);
	void update(double dt);
	void render(sf::RenderWindow & window);

	void increaseSpeed();
	void decreaseSpeed();
	void increaseRotation();
	void DecreaseRotation();
	void handleKeyInput();
	void increaseTurretRotation();
	void decreaseTurretRotation();

	double m_speed{ 0.0 };
	double m_rotation{0.0};

	double m_turretRotation{ 0.0 };

	KeyHandler const &m_keyHandler;

private:
	void initSprites(sf::Vector2f const & pos);
	sf::Sprite m_tankBase;
	sf::Sprite m_turret;
	sf::Texture const & m_texture;

	double static const DEG_TO_RAD;
		
};
