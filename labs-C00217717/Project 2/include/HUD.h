#ifndef HUDCLASS

#include <iostream>
#include "Tank.h"
#include "TankAI.h"
#include "PickUp.h"
#include "GameState.h"
#include <SFML\Graphics.hpp>
class HUD
{
public:
	HUD(sf::Font & hudfont);

	void update(GameState const & t_state, Tank & t_tank, TankAi & t_aiTank, PickUp & m_Health);
	void render(sf::RenderWindow & t_window);

	sf::Font m_textFont;
private:
	
	sf::Text m_gamestateText;
	sf::Text m_enemyHealth;
	sf::Text m_playerHealth;
	sf::Text m_pickupAvailable;
	sf::RectangleShape m_hudOutline;
};
#endif // !HUD
