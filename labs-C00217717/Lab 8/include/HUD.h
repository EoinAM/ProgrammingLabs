#ifndef HUDCLASS

#include <iostream>
#include "GameState.h"
#include <SFML\Graphics.hpp>
class HUD
{
public:
	HUD(sf::Font & hudfont);

	void update(GameState const & t_state);
	void render(sf::RenderWindow & t_window);

private:
	sf::Font m_textFont;
	sf::Text m_gamestateText;
	sf::RectangleShape m_hudOutline;
};
#endif // !HUD
