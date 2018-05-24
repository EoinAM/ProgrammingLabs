/// <summary>
/// @Author Eoin Abbey-Maher
/// </summary>

#ifndef PADDLE
#define PADDLE

#include <SFML\Graphics.hpp>
#include "KeyHandler.h"
#include "ScreenSize.h"

class Paddle
{
public:
	/// <summary>
	/// Default Constructor
	/// </summary>
	/// <param name="t_keyHandler">Passed a reference of the Keyhandler from the Game CLass</param>
	Paddle(KeyHandler const& t_keyHandler);

	/// <summary>
	/// Default Destructor
	/// </summary>
	~Paddle();
	
	void render(sf::RenderWindow & t_window);
	void update();

	/// <summary>
	/// Paddle Movement Speed
	/// </summary>
	float m_speed;

	/// <summary>
	/// Values that will be setup from Yaml File
	/// </summary>
	sf::Vector2f m_size;
	sf::Vector2f m_startPosition;
	sf::Vector2f m_position;

	sf::RectangleShape m_body;
	
	/// <summary>
	/// Reference setup for Keyhandler 
	/// </summary>
	KeyHandler const & m_keyHandler;

private:
	/// <summary>
	/// Function to Deal with Key presses
	/// </summary>
	void handleKeyInput();
};



#endif // !PADDLE
