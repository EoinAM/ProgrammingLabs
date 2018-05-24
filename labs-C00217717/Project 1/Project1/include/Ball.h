/// <summary>
/// @Author Eoin Abbey-Maher
/// </summary>

#ifndef BALL
#define BALL

#include "Block.h"
#include "ScreenSize.h"
#include "Enemy.h"
#include "Paddle.h"
#include "KeyHandler.h"

#include <iostream>
#include <SFML\Graphics.hpp>

class Ball
{
public:
	/// <summary>
	/// Default Constructor
	/// </summary>
	/// <param name="t_keyHandler"> Passed the Keyhandler from the Game Class</param>
	Ball(KeyHandler & t_keyHandler);

	/// <summary>
	/// Default Destructor
	/// </summary>
	~Ball();


	void update();
	void render(sf::RenderWindow & t_window);
	
	/// <summary>
	/// function to reset the ball object after it goes
	/// out of the play area
	/// </summary>
	void reset();

	/// <summary>
	/// Functions to test for colisiions between the ball and 
	/// other on screen objects
	/// 
	/// Passed references to the Paddle, Blocks and Enemies from the Game Class
	/// </summary>
	void m_collisionBlock(Block & t_block);
	void m_collisionEnemy(Enemy& t_enemy);
	void m_collisionPaddle(Paddle & t_paddle);
	void m_collisionWall();

	/// <summary>
	/// Setups for when the Game is started
	/// </summary>
	sf::Vector2f m_startingVector{ 2,2 };
	sf::Vector2f m_startPosition;
	

	sf::Vector2f m_DirectionVector{ 2,2 };
	sf::Vector2f m_position;
	sf::Vector2f m_lastPosition;

	sf::CircleShape m_body;
	
	int m_boostUsages{ 3 };
	int m_score{ 0 };
	int m_timer{ 120 };
	int m_subtimer{ 0 };
	
	float m_speed{ 3 };

	/// <summary>
	/// Booleans for if the Ball is to be drawn
	///  & for if the ball is dead or not
	/// </summary>
	bool m_isShown;
	bool m_dead{ false };
private:

	/// <summary>
	/// Variables for the Collision
	/// </summary>
	float m_hitDistance{ 0.0f };
	float m_deflection{ 0.0f };
	float m_angle{ 0.0f };

	/// <summary>
	/// Timer activated when the power up is used
	/// </summary>
	int m_boostTimer{ 0 };

	void boost();
	void move();
	
	/// <summary>
	/// Booleans for if the ball is moving and if it is powered up
	/// </summary>
	bool m_moving{ false };
	bool m_boosted{ false };
	
	KeyHandler & m_keyHandler;
};


#endif // !BALL
