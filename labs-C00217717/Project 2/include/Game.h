
 #pragma once
#include <SFML/Graphics.hpp>
#include "ScreenSize.h"
#include "LevelLoader.h"
#include "Tank.h"
#include "KeyHandler.h"
#include <TankAI.h>
#include "PickUp.h"
#include "GameState.h"
#include "HUD.h"

/// <summary>
/// @author RP
/// @date June 2017
/// @version 1.0
/// 
/// </summary>

/// <summary>
/// @brief Main class for the SFML Playground project.
/// 
/// This will be a single class framework for learning about SFML. 
/// Example usage:
///		Game game;
///		game.run();
/// </summary>

class Game
{
public:
	/// <summary>
	/// @brief Default constructor that initialises the SFML window, 
	///   and sets vertical sync enabled. 
	/// </summary>
	Game();

	/// <summary>
	/// @brief the main game loop.
	/// 
	/// A complete loop involves processing SFML events, updating and drawing all game objects.
	/// The actual elapsed time for a single game loop results (lag) is stored. If this value is 
	///  greater than the notional time for one loop (MS_PER_UPDATE), then additional updates will be 
	///  performed until the lag is less than the notional time for one loop.
	/// The target is one update and one render cycle per game loop, but slower PCs may 
	///  perform more update than render operations in one loop.
	/// </summary>
	void run();

	LevelData m_level;
	LevelLoader m_levelLoader;
	
	PickUp m_healthPickUp;
protected:

	void generateWalls();

	/// <summary>
	/// @brief Placeholder to perform updates to all game objects.
	/// </summary>
	/// <param name="time">update delta time</param>
	void update(double dt);

	/// <summary>
	/// @brief Draws the background and foreground game objects in the SFML window.
	/// The render window is always cleared to black before anything is drawn.
	/// </summary>
	void render();

	/// <summary>
	/// @brief Checks for events.
	/// Allows window to function and exit. 
	/// Events are passed on to the Game::processGameEvents() method.
	/// </summary>	
	void processEvents();

	/// <summary>
	/// @brief Handles all user input.
	/// </summary>
	/// <param name="event">system event</param>
	void processGameEvents(sf::Event&);

	// main window
	sf::RenderWindow m_window;
	sf::Texture m_bgTexture;
	sf::Sprite m_bgSprite;

	std::vector<sf::Sprite> m_sprites;

	sf::Sprite sprite;
	Tank m_tank;

	TankAi m_aiTank;
	sf::Texture m_texture;

	std::vector<sf::Sprite> m_wallSprites;

	sf::Font m_font;
	HUD m_hud;

	int m_restartTimer{ 0 };

	KeyHandler m_keyhandler;

	int m_aiShotTimer{ 1000 };
	int m_tankShotTimer{ 1000 };

	GameState m_gameState{ GameState::GAME_RUNNING };
	
};
