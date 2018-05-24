#include "..\include\HUD.h"

HUD::HUD(sf::Font & hudfont) :
	m_textFont(hudfont)
{
	m_gamestateText.setFont(hudfont);
	m_gamestateText.setCharacterSize(30);
	m_gamestateText.setFillColor(sf::Color::White);
	m_gamestateText.setPosition(sf::Vector2f(600, 3));
	m_gamestateText.setString("Game Running");

	m_hudOutline.setSize(sf::Vector2f(1440.0f, 40.0f));
	m_hudOutline.setFillColor(sf::Color(0, 0, 0, 40));
	m_hudOutline.setOutlineThickness(-.5);
	m_hudOutline.setOutlineColor(sf::Color(0, 0, 0, 100));
	m_hudOutline.setPosition(0, 0);
}

void HUD::update(GameState const & t_state)
{
	switch (t_state)
	{
	case GameState::GAME_RUNNING:
		m_gamestateText.setString("Game Running");
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
}
