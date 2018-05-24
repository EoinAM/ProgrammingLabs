/// <summary>
/// @Author Eoin Abbey-Maher
/// </summary>

#include "Paddle.h"
	
/// <summary>
/// Default Constructor
/// 
/// Keyhandler initialised with keyhandler passed from the Game class 
/// </summary>
/// <param name="t_keyHandler"></param>
Paddle::Paddle(KeyHandler const & t_keyHandler):
	m_keyHandler(t_keyHandler)
{
}

Paddle::~Paddle()
{
}

void Paddle::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_body);
}

void Paddle::update()
{
	handleKeyInput();
	m_body.setPosition(m_position);
}

/// <summary>
/// Function to check Key handler
/// 
/// When the left or Right Keys are pressed the Paddle is moved in the corresponding Direction
/// </summary>
void Paddle::handleKeyInput()
{
	if (m_keyHandler.isPressed(sf::Keyboard::Left))
	{
		if (m_position.x > m_body.getGlobalBounds().width * .5)
		{
			m_position.x -= m_speed;
		}
	}


	if (m_keyHandler.isPressed(sf::Keyboard::Right))
	{
		{
			if (m_position.x < ScreenSize::s_width - (m_body.getGlobalBounds().width * .5))
			{
				m_position.x += m_speed;
			}
		}
	}
}

