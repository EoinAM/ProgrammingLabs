/// <summary>
/// @Author Eoin Abbey-Maher
/// </summary>

#ifndef ENEMY
#define ENEMY

#include "SFML\Graphics.hpp"
#include "ScreenSize.h"


class Enemy
{
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	Enemy();

	/// <summary>
	/// Default Destructor
	/// </summary>
	~Enemy();

	/// <summary>
	/// Function to update Enemy Object
	/// </summary>
	/// <param name="t_movespeed"> passed the movement speed from the Game class</param>
	void update(float t_movespeed);
	
	void render(sf::RenderWindow & t_window);
	
	/// <summary>
	/// Function to move the Enemy Object
	/// </summary>
	/// <param name="t_speed">passed the movement speed from the Game class</param>
	void move(float t_speed);

	/// <summary>
	/// Boolean to show if the enemies are to change direction
	/// </summary>
	bool m_dirSwap{ false };
	bool m_isShown;

	sf::Vector2f m_position;
	sf::Vector2f m_size;
	sf::RectangleShape m_body;

private:
};

#endif // !enemy


