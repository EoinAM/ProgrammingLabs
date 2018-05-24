/// <summary>
/// @Author Eoin Abbey-Maher
/// </summary>

#ifndef GAME
#define GAME


#include "ScreenSize.h"
#include "LevelLoader.h"
#include "Enemy.h"
#include "Block.h"
#include "Paddle.h"
#include "KeyHandler.h"
#include "Ball.h"

#include <SFML\Graphics.hpp>
#include <iostream>

/// <summary>
/// Enum for the gameState to show 
/// what screen is being drawn on screen and what update is running
/// </summary>
enum GameState
{
	PLAYING,
	GAMEOVER
};


class Game
{
public:
	/// <summary>
	/// Default constructor
	/// </summary>
	Game();

	/// <summary>
	/// Default Destructor
	/// </summary>
	~Game() {};

	void run();

	/// <summary>
	/// Keyhandler Object to check for button presses and to be passed to other objects
	/// </summary>
	KeyHandler m_keyhandler;

	/// <summary>
	/// Level data to Load data into from the YAML level loader
	/// </summary>
	LevelData m_level;
protected:
	void update(double t_dt);
	void render();
	void processEvents();
	void ProcessGameEvents(sf::Event &);

	/// <summary>
	/// Assign Values from Yaml file to objects
	/// </summary>
	void setupYamlObjects();

	/// <summary>
	/// Set up text Objects
	/// </summary>
	void setupText();

	/// <summary>
	/// Funciton to reset all objects back to there starting position
	/// </summary>
	void restart();

	Paddle m_paddle;
	Ball m_ball;


	sf::Font m_font;
	sf::Text m_scoreText;
	sf::Text m_powerUpText;
	sf::Text m_timerText;
	sf::Text m_gameOverText;
	
	
	sf::RenderWindow m_window;
	
	/// <summary>
	/// Vectors To hold Enemy And Brick objects
	/// </summary>
	std::vector<Enemy> m_enemies;
	std::vector<Block> m_bricks;

	/// <summary>
	/// Boolean to check if enemies should change direction
	/// </summary>
	bool m_enemySwap{ false };
	
	float m_enemyMoveSpeed{ 1 };

	int m_finalScore{0};
	
	GameState m_currentGameState{GameState::PLAYING};
};


#endif // !GAME


