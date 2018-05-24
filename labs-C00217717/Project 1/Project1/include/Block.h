/// <summary>
/// @Author Eoin Abbey-Maher
/// </summary>

#ifndef BLOCK
#define BLOCK

#include "ScreenSize.h"
#include "Enemy.h"
#include <SFML\Graphics.hpp>

class Block
{
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	Block();


	~Block();

	void render(sf::RenderWindow & t_window);
		
	bool m_isShown;

	sf::Vector2f m_position;
	sf::Vector2f m_size;

	sf::RectangleShape m_body;
private: 

};
#endif // !BLOCK



