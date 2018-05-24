/// <summary>
/// @Author Eoin Abbey-Maher
/// </summary>

#ifndef KEYHANDLER
#define KEYHANDLER

#include <map>
#include <SFML\Window\Keyboard.hpp>

class KeyHandler
{
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	KeyHandler();

	/// <summary>
	/// Default Destructor
	/// </summary>
	~KeyHandler();

	void updateKey(sf::Keyboard::Key t_key, bool t_isPressed);
	
	/// <summary>
	/// Boolean for if the key is being pressed or not
	/// </summary>
	bool isPressed(sf::Keyboard::Key t_key) const; 

private:

	typedef std::map<sf::Keyboard::Key, bool> Keymap;

	Keymap m_keyMap;
};



#endif // !KEYHANDLER
