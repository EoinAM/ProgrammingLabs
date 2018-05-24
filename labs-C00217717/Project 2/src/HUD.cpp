#include "..\include\HUD.h"


HUD::HUD(sf::Font & hudfont) :m_textFont(hudfont)
{
	m_gamestateText.setFont(hudfont);
	m_gamestateText.setCharacterSize(15);
	m_gamestateText.setFillColor(sf::Color::White);
	m_gamestateText.setPosition(sf::Vector2f(600, 3));
	m_gamestateText.setString("Game Running");

	m_enemyHealth.setFont(hudfont);
	m_enemyHealth.setCharacterSize(30);
	m_enemyHealth.setFillColor(sf::Color::White);
	m_enemyHealth.setPosition(sf::Vector2f(1000, 3));
	m_enemyHealth.setString("AI Health: 100");

	m_pickupAvailable.setFont(hudfont);
	m_pickupAvailable.setCharacterSize(15);
	m_pickupAvailable.setFillColor(sf::Color::White);
	m_pickupAvailable.setPosition(sf::Vector2f(600, 20));
	m_pickupAvailable.setString("Pickup Available");

	m_playerHealth.setFont(hudfont);
	m_playerHealth.setCharacterSize(30);
	m_playerHealth.setFillColor(sf::Color::White);
	m_playerHealth.setPosition(sf::Vector2f(200, 3));
	m_playerHealth.setString("Health: 100");

	m_hudOutline.setSize(sf::Vector2f(1440.0f, 40.0f));
	m_hudOutline.setFillColor(sf::Color(0, 0, 0, 40));
	m_hudOutline.setOutlineThickness(-.5);
	m_hudOutline.setOutlineColor(sf::Color(0, 0, 0, 100));
	m_hudOutline.setPosition(0, 0);
}

void HUD::update(GameState const & t_state, Tank & t_tank, TankAi & t_aiTank, PickUp & m_Health)
{
	switch (t_state)
	{
	case GameState::GAME_RUNNING:
		m_gamestateText.setString("Game Running");
		
		m_enemyHealth.setString("AI Health: " + std::to_string(t_aiTank.m_health));
		m_playerHealth.setString("Health: " + std::to_string(t_tank.m_health));
		
		if (m_Health.m_isAvailable)
		{
			m_pickupAvailable.setString("Pickup Available");
		}
		else
		{
			m_pickupAvailable.setString("Pickup Not Available");
		}

		break;
	case GameState::GAME_WIN:
		m_gamestateText.setString("You Win");
		break;
	case GameState::GAME_LOSE:
		m_gamestateText.setString("You Lose");
		break;
	default:
		break;
	}
}

void HUD::render(sf::RenderWindow & t_window)
{
	t_window.draw(m_hudOutline);
	t_window.draw(m_gamestateText);
	t_window.draw(m_enemyHealth);
	t_window.draw(m_pickupAvailable);
	t_window.draw(m_playerHealth);
}
