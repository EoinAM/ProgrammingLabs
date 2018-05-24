/// <summary>
/// @Author Eoin Abbey-Maher
/// </summary>
#include "Ball.h"


Ball::Ball(KeyHandler & t_keyHandler) :
	m_keyHandler(t_keyHandler)
{
	m_body.setFillColor(sf::Color::White);
	m_body.setRadius(10);
	m_body.setOrigin(m_body.getRadius(), m_body.getRadius());
}

Ball::~Ball()
{
}

void Ball::update()
{
	m_lastPosition = m_position;
	m_body.setPosition(m_position);
	m_collisionWall();
	move();

	m_subtimer++;
	if (m_subtimer == 100)
	{
		m_timer--;
		m_subtimer = 0;
	}

	if (m_boosted)
	{
		m_boostTimer++;
	}
}

void Ball::render(sf::RenderWindow & t_window)
{
	if (m_dead == false)
	{
		t_window.draw(m_body);
	}

}

/// <summary>
/// Function to reset the ball after it has gone out of the play area
/// </summary>
void Ball::reset()
{
	m_dead = true;
	m_position = m_startPosition;
	m_body.setPosition(m_startPosition);
	m_DirectionVector = m_startingVector;
	m_boostTimer = 0;
	m_speed = 3;
	m_moving = false;

	m_dead = false;
}

/// <summary>
/// Function for using the Power up on the Ball
/// 
/// Depending on the direction of the ball changes what way is applied to the speed,
/// 
/// When the Boost timer becomes 600 the boost stops and resets the speed back to its original speed
/// 
/// </summary>
void Ball::boost()
{
	if (m_boosted && m_boostUsages > 0)
	{
		if (m_boostTimer == 0)
		{
			if (m_DirectionVector.y < 0 && m_DirectionVector.x < 0)
			{
				m_speed = 6;
			}
			if (m_DirectionVector.y < 0 && m_DirectionVector.x > 0)
			{
				m_speed = -6;
			}
			if (m_DirectionVector.y > 0 && m_DirectionVector.x < 0)
			{
				m_speed = 6;
			}
			if (m_DirectionVector.y > 0 && m_DirectionVector.x > 0)
			{
				m_speed = 6;
			}
			m_DirectionVector.x = cos(m_angle) * m_speed;
			m_DirectionVector.y = sin(m_angle) * m_speed;
			m_boostUsages--;
		}
	}
	if (m_boostTimer >= 600)
	{
		m_boostTimer = 0;
		m_boosted = false;
		if (m_DirectionVector.y < 0 && m_DirectionVector.x < 0)
		{
			m_speed = 3;
		}
		if (m_DirectionVector.y < 0 && m_DirectionVector.x > 0)
		{
			m_speed = 3;
		}
		if (m_DirectionVector.y > 0 && m_DirectionVector.x < 0)
		{
			m_speed = -3;
		}
		if (m_DirectionVector.y > 0 && m_DirectionVector.x > 0)
		{
			m_speed = -3;
		}
		m_DirectionVector.x = cos(m_angle) * m_speed;
		m_DirectionVector.y = sin(m_angle) * m_speed;
	}
}



/// <summary>
/// Keyhandler to Check when the buttons are being Pressed to start the Power up 
///  & to start the ball moving
/// </summary>
void Ball::move()
{
	if (m_keyHandler.isPressed(sf::Keyboard::Space) & m_moving == false)
	{
		m_moving = true;
	}

	if (m_moving)
	{
			m_position += m_DirectionVector;
	}

	if (m_keyHandler.isPressed(sf::Keyboard::Up) && m_moving && m_boosted == false )
	{
		m_boosted = true;
	}

	boost();

}

/// <summary>
/// Function to check the collision between the ball and the block
/// 
/// When the ball hits the block it will deflect away, also making the block dissapear
/// It adds 10 to the Players Score
/// </summary>
/// <param name="t_brick">Reference to the brick from the game class</param>
void Ball::m_collisionBlock(Block & t_brick)
{
	if (t_brick.m_isShown)
	{
		//Bottom
		if (m_position.x - m_body.getRadius() >= t_brick.m_position.x && m_position.x + m_body.getRadius() <= (t_brick.m_position.x + t_brick.m_size.x)
			&& (m_position.y - m_body.getRadius()) <= t_brick.m_position.y + t_brick.m_size.y && (m_position.y - m_body.getRadius()) > t_brick.m_position.y)
		{
			m_position = m_lastPosition;
			m_DirectionVector.y *= -1;
			t_brick.m_isShown = false;
			m_score += 10;
		}

		//Left
		if (m_position.x + m_body.getRadius() >= t_brick.m_position.x && m_position.x + m_body.getRadius() <= t_brick.m_position.x
			&& m_position.y >= t_brick.m_position.y &&  m_position.y <= t_brick.m_position.y + t_brick.m_size.y)
		{
			m_position = m_lastPosition;
			m_DirectionVector.x *= -1;
			t_brick.m_isShown = false;
			m_score += 10;
		}

		//Right
		if (m_position.x - m_body.getRadius() <= t_brick.m_position.x + t_brick.m_size.x && m_position.x + m_body.getRadius() >= t_brick.m_position.x
			&& m_position.y >= t_brick.m_position.y &&  m_position.y <= t_brick.m_position.y + t_brick.m_size.y)
		{
			m_position = m_lastPosition;
			m_DirectionVector.x *= -1;
			t_brick.m_isShown = false;
		}

		//Top
		if (m_position.x >= t_brick.m_position.x && m_position.x <= (t_brick.m_position.x + t_brick.m_size.x)
			&& (m_position.y + m_body.getRadius()) >= t_brick.m_position.y && (m_position.y + m_body.getRadius()) < t_brick.m_position.y + t_brick.m_size.y)
		{
			m_position = m_lastPosition;
			m_DirectionVector.y *= -1;
			t_brick.m_isShown = false;
			m_score += 10;
		}

		
	}
}

/// <summary>
/// Function to check the collision between the ball and the enemy
/// 
/// When the ball hits the enemy it will deflect away, also making the block dissapear
/// It adds 15 to the Players Score
/// </summary>
void Ball::m_collisionEnemy(Enemy & t_enemy)
{
	if (t_enemy.m_isShown)
	{
		//Bottom
		if (m_position.x - m_body.getRadius() >= t_enemy.m_position.x && m_position.x + m_body.getRadius() <= (t_enemy.m_position.x + t_enemy.m_size.x)
			&& (m_position.y - m_body.getRadius()) <= t_enemy.m_position.y + t_enemy.m_size.y && (m_position.y - m_body.getRadius()) > t_enemy.m_position.y)
		{
			m_position = m_lastPosition;
			m_score += 15;
			m_DirectionVector.y *= -1;
			t_enemy.m_isShown = false;

		}

		//Left
		if (m_position.x + m_body.getRadius() >= t_enemy.m_position.x && m_position.x + m_body.getRadius() <= t_enemy.m_position.x
			&& m_position.y >= t_enemy.m_position.y &&  m_position.y <= t_enemy.m_position.y + t_enemy.m_size.y)
		{
			m_score += 15;
			m_position = m_lastPosition;
			m_DirectionVector.x *= -1;
			t_enemy.m_isShown = false;
		}

		//Right
		if (m_position.x - m_body.getRadius() <= t_enemy.m_position.x + t_enemy.m_size.x && m_position.x + m_body.getRadius() >= t_enemy.m_position.x
			&& m_position.y >= t_enemy.m_position.y &&  m_position.y <= t_enemy.m_position.y + t_enemy.m_size.y)
		{
			m_position = m_lastPosition;
			m_score += 15;
			m_DirectionVector.x *= -1;
			t_enemy.m_isShown = false;
		}

		//Top
		if (m_position.x >= t_enemy.m_position.x && m_position.x <= (t_enemy.m_position.x + t_enemy.m_size.x)
			&& (m_position.y + m_body.getRadius()) >= t_enemy.m_position.y && (m_position.y + m_body.getRadius()) < t_enemy.m_position.y + t_enemy.m_size.y)
		{
			m_position = m_lastPosition;
			m_DirectionVector.y *= -1;
			m_score += 15;
			t_enemy.m_isShown = false;
		}


	}
}

/// <summary>
/// Function for collision between the ball and the paddle
/// 
/// When the ball hits the paddle it gets its position from the nearest corner, 
/// It the finds the angle for the ball to deflect at,
/// this is then turned int a Direction vector that is used to move the ball
/// </summary>
/// <param name="t_paddle"></param>
void Ball::m_collisionPaddle(Paddle  & t_paddle)
{
	//Right Side
	if (m_position.x > t_paddle.m_position.x && m_position.x < (t_paddle.m_position.x + (t_paddle.m_size.x * .5))
		&& (m_position.y + m_body.getRadius()) >= t_paddle.m_position.y)
	{
		m_position.y -= 2;
		m_hitDistance = m_position.x - (t_paddle.m_position.x + t_paddle.m_size.x * .5);

		m_deflection = (m_hitDistance / t_paddle.m_size.x )- t_paddle.m_size.x * .5;
		m_angle = 90 - (90 * abs(m_deflection));
		
		m_DirectionVector.x = cos(m_angle) * m_speed;
		m_DirectionVector.y = sin(m_angle) * m_speed;

	}	

	//Left side
	if (m_position.x < t_paddle.m_position.x && m_position.x > (t_paddle.m_position.x - (t_paddle.m_size.x * .5))
		&& (m_position.y + m_body.getRadius()) >= t_paddle.m_position.y)
	{
		m_position.y -= 2;
		m_hitDistance = m_position.x - (t_paddle.m_position.x - t_paddle.m_size.x * .5);

		m_deflection = (m_hitDistance / t_paddle.m_size.x) - t_paddle.m_size.x * .5;
		m_angle = (90 - (90 * abs(m_deflection))) *-1;

		m_DirectionVector.x = cos(m_angle) * m_speed;
		m_DirectionVector.y = sin(m_angle) * m_speed;
	}

	if (m_position.x == t_paddle.m_position.x && (m_position.y + m_body.getRadius()) == t_paddle.m_position.y)
	{
		m_position.y -= 2;
		m_angle = 90;
		m_DirectionVector.x = cos(m_angle) * m_speed;
		m_DirectionVector.y = sin(m_angle) * m_speed;
	}
	 //Left Corner
	if (m_position.x == (t_paddle.m_position.x - (t_paddle.m_size.x * .5))
		&& (m_position.y + m_body.getRadius()) >= t_paddle.m_position.y)
	{
		m_position.y -= 2;
		m_angle = 45;
		m_DirectionVector.x = cos(m_angle) * m_speed;
		m_DirectionVector.y = sin(m_angle) * m_speed;
	}

	//Right Corner
	if (m_position.x == (t_paddle.m_position.x + (t_paddle.m_size.x * .5))
		&& (m_position.y + m_body.getRadius()) >= t_paddle.m_position.y)
	{
		m_position.y -= 2;
		
		m_angle = 45;
		m_DirectionVector.x = cos(m_angle) * m_speed;
		m_DirectionVector.y = sin(m_angle) * m_speed;
	}

	if (m_position.y >=t_paddle.m_position.y + t_paddle.m_size.y )
	{
		m_timer -= 4;
		reset();
	}
}

/// <summary>
/// Function to check if the ball hits the Borders of the screen
/// Depending on where it hits decides if it has its X or Y reversed
/// </summary>
void Ball::m_collisionWall()
{
	if (m_position.x <= 0)
	{
		m_position = m_lastPosition;

		m_DirectionVector.x *= -1;

		m_position += m_DirectionVector;
	}

	if (m_position.x >= ScreenSize::s_width - (m_body.getRadius()))
	{
		m_position = m_lastPosition;

		m_DirectionVector.x *= -1;

		m_position += m_DirectionVector;
	}
	if (m_position.y <= 0)
	{
		m_position = m_lastPosition;

		m_DirectionVector.y *= -1;

		m_position += m_DirectionVector;
	}

}

