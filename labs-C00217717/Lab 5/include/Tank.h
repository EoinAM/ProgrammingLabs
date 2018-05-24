#pragma once
#include <SFML/Graphics.hpp>
#include "KeyHandler.h"
#include <CollisionDetector.h>

#include <Thor\Math.hpp>
/// <summary>
/// @brief A simple tank controller.
/// 
/// This class will manage all tank movement and rotations.
/// </summary>


class Tank
{
public:	
	Tank(sf::Texture const & texture, std::vector<sf::Sprite> & m_wallSprites, sf::Vector2f const & pos, KeyHandler const & t_keyHandler);
	void update(double dt);
	void render(sf::RenderWindow & window);

	void increaseSpeed();
	void decreaseSpeed();
	void increaseRotation();
	void DecreaseRotation();
	void handleKeyInput();
	void increaseTurretRotation();
	void decreaseTurretRotation();

	void deflect();
	void adjustRotation();

	double m_speed{ 0.0 };
	double m_rotation{0.0};

	sf::Vector2f m_previousPosition{ 0,0 };

	double m_previousSpeed{ 0.0 };
	double m_previousRotation{ 0.0 };
	double m_previousTurretRotation{ 0.0 };

	bool m_enableRotation{ true };

	double m_turretRotation{ 0.0 };

	KeyHandler const &m_keyHandler;

private:
	std::vector<sf::Sprite> & m_wallSprites;

	bool checkWallCollisions();

	void initSprites(sf::Vector2f const & pos);
	sf::Sprite m_tankBase;
	sf::Sprite m_turret;
	sf::Texture const & m_texture;

	double static const DEG_TO_RAD;
		
};
