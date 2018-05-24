/// <summary>
/// @Author Eoin Abbey-Maher
/// </summary>
#include "KeyHandler.h"

/// <summary>
/// Key default constructor
/// </summary>
KeyHandler::KeyHandler()
{
}

/// <summary>
/// Default destructor
/// </summary>
KeyHandler::~KeyHandler()
{
}

/// <summary>
/// Function to check for key press
/// </summary>
/// <param name="t_key">takes in Key currently being pressed</param>
/// <param name="t_isPressed">sets bool to be true</param>
void KeyHandler::updateKey(sf::Keyboard::Key t_key, bool t_isPressed)
{
	m_keyMap[t_key] = t_isPressed;
}


bool KeyHandler::isPressed(sf::Keyboard::Key t_key) const
{
	Keymap::const_iterator it = m_keyMap.find(t_key);

	if (it != m_keyMap.end())
	{
		return it->second;	
	}
	return false;
}
