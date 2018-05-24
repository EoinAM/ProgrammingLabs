/// <summary>
/// @Author Eoin Abbey-Maher
/// </summary> 

#include "Game.h"

static double const MS_PER_UPDATE = 10.0;

/// <summary>
/// Default constructor
/// 
/// paddle and Ball objects are passed KeyHandler through initialiser list
/// 
/// Data is loaded in through Level Loader and Font file is loaded
/// </summary>
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_width, ScreenSize::s_height, 32), "Space Invaders", sf::Style::Default),
	m_paddle(m_keyhandler),
	m_ball(m_keyhandler)
{
	/// <summary>
	/// Vsync locks the game to refresh at the same rate as the monitor it is 
	///  Running on
	/// </summary>
	m_window.setVerticalSyncEnabled(true);

	int currentLevel{ 1 };
	if (!LevelLoader::load(currentLevel, m_level))
	{
		return;
	}

	if (!m_font.loadFromFile("resources\\fonts\\Reckoner.ttf"))
	{
		std::cout << "Font not loaded" << std::endl;
	}

	setupYamlObjects();
	setupText();

}

/// <summary>
/// Game Cycle To Run Whilst the game is open
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();
		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
}

/// <summary>
/// Process Events with the Window
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}

		ProcessGameEvents(event);
	}
}

/// <summary>
/// Funtion to Process events that effect the game
/// </summary>
/// <param name="t_event">event passed from the process events function</param>
void Game::ProcessGameEvents(sf::Event & t_event)
{
	switch (t_event.type)
	{
	case sf::Event::KeyPressed:
		m_keyhandler.updateKey(t_event.key.code, true);
		break;

	case sf::Event::KeyReleased:
		m_keyhandler.updateKey(t_event.key.code, false);
		break;
	default:
		break;
	}
	if (sf::Event::KeyPressed == t_event.type)
	{
		switch (t_event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;

		default:
			break;
		}
	}
}

/// <summary>
/// Update to run depending on the game state
/// </summary>
/// <param name="t_dt"></param>
void Game::update(double t_dt)
{

	switch (m_currentGameState)
	{

	case PLAYING:
		m_paddle.update();
		m_ball.m_collisionPaddle(m_paddle);
		m_ball.update();

		/// <summary>
		/// Update to check if the enemy should change direction
		/// 
		/// tests each enemy object to see if their bool has been changed and
		///  the y have hit one of the sides, then multiples the move speed for 
		///  all enemies by -1 to change the direction its moving in
		/// </summary>
		for (auto & enemy : m_enemies)
		{
			enemy.update(m_enemyMoveSpeed);
			m_ball.m_collisionEnemy(enemy);
			if (enemy.m_dirSwap)
			{
				m_enemySwap = true;
				m_enemyMoveSpeed *= -1;
				enemy.m_dirSwap = false;
			}
		}

		for (auto & brick : m_bricks)
		{
			m_ball.m_collisionBlock(brick);
		}

		m_timerText.setString("Time Left : " + std::to_string(m_ball.m_timer));
		m_powerUpText.setString("Power Ups : " + std::to_string(m_ball.m_boostUsages));
		m_scoreText.setString("Score : " + std::to_string(m_ball.m_score));

		/// <summary>
		/// If the Timer runs out the game is over, changes the game state to be Game Over
		/// </summary>
		if (m_ball.m_timer <= 0)
		{
			m_finalScore = m_ball.m_score;
			m_gameOverText.setString("\t \t Game Over \n Press Space To Restart \n \t \t Final Score : " + std::to_string(m_finalScore));
			m_currentGameState = GameState::GAMEOVER;

		}
		break;
	case GAMEOVER:
		if (m_keyhandler.isPressed(sf::Keyboard::Space))
		{
			restart();
		}
		break;
	default:
		break;
	}
	
}

/// <summary>
/// Render function oto draw all the items on the screen
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));

	switch (m_currentGameState)
	{
	case PLAYING:
		for (auto & enemy : m_enemies)
		{
			enemy.render(m_window);
		}


		m_paddle.render(m_window);

		for (auto & brick : m_bricks)
		{
			brick.render(m_window);
		}
		m_ball.render(m_window);

		m_window.draw(m_timerText);
		m_window.draw(m_scoreText);
		m_window.draw(m_powerUpText);
		break;
	case GAMEOVER:
		m_window.draw(m_gameOverText);
		break;
	default:
		break;
	}
	
	m_window.display();	
}

/// <summary>
/// Function to setup all the Data loaded form the YAML file and assign them to the game objects
///
/// </summary>
void Game::setupYamlObjects()
{
	/// <summary>
	/// Range based loop using the amount of "m_enemies" types in the YAML file to 
	///  set Up enemy Objects and assign them to the vector
	/// </summary>
	for (EnemyData const & enemy : m_level.m_enemies)
	{
		Enemy enemyObject;
		enemyObject.m_position = enemy.m_position;
		enemyObject.m_size = enemy.m_size;
		enemyObject.m_body.setSize(enemy.m_size);
		enemyObject.m_isShown = enemy.m_shown;
		enemyObject.m_body.setFillColor(sf::Color::Red);
		enemyObject.m_body.setPosition(enemyObject.m_position);
		m_enemies.push_back(enemyObject);
	}

	for (BrickData const & brick : m_level.m_bricks)
	{
		Block brickObject;
		brickObject.m_size = brick.m_size;
		brickObject.m_body.setSize(brick.m_size);
		brickObject.m_isShown = brick.m_shown;
		brickObject.m_position = brick.m_position;
		brickObject.m_body.setPosition(brickObject.m_position);
		brickObject.m_body.setFillColor(sf::Color::Blue);
		m_bricks.push_back(brickObject);
	}

	m_paddle.m_size = m_level.m_paddle.m_size;
	m_paddle.m_body.setSize(m_paddle.m_size);
	m_paddle.m_startPosition = m_level.m_paddle.m_position;
	m_paddle.m_position = m_paddle.m_startPosition;
	m_paddle.m_body.setPosition(m_paddle.m_startPosition);
	m_paddle.m_speed = m_level.m_paddle.m_moveSpeed;
	m_paddle.m_body.setOrigin(m_paddle.m_size.x * .5, 0);
	m_paddle.m_body.setFillColor(sf::Color::Blue);

	m_ball.m_startPosition = m_level.m_ball.m_position;
	m_ball.m_position = m_ball.m_startPosition;
	m_ball.m_body.setPosition(m_ball.m_position);
	m_ball.m_isShown = m_level.m_ball.m_shown;
}

void Game::setupText()
{
	m_scoreText.setFont(m_font);
	m_powerUpText.setFont(m_font);
	m_timerText.setFont(m_font);
	m_gameOverText.setFont(m_font);

	m_timerText.setFillColor(sf::Color::White);
	m_powerUpText.setFillColor(sf::Color::White);
	m_scoreText.setFillColor(sf::Color::White);
	m_gameOverText.setFillColor(sf::Color::White);

	m_timerText.setPosition(850,620);
	m_powerUpText.setPosition(450, 620);
	m_scoreText.setPosition(100, 620);
	m_gameOverText.setPosition(ScreenSize::s_height * .5, ScreenSize::s_width* .5);
	
	m_timerText.setCharacterSize(40);
	m_powerUpText.setCharacterSize(40);
	m_scoreText.setCharacterSize(40);
	m_gameOverText.setCharacterSize(100);

	m_timerText.setString("Time Left :100!");
	m_powerUpText.setString("Power Ups : " + std::to_string(m_ball.m_boostUsages));
	m_scoreText.setString("Score : " + std::to_string(m_ball.m_score));
	m_gameOverText.setString("\t \t Game Over \n Press Space To Restart \n \t \t Final Score : " + std::to_string(m_finalScore));

	m_gameOverText.setOrigin(m_gameOverText.getGlobalBounds().height* .5, m_gameOverText.getGlobalBounds().width* .5);
}

/// <summary>
/// Funtion to restart the game back to the Original Starting Screen,
/// Moves all objects back to their starting position and resets scores and timers
/// </summary>
void Game::restart()
{
	setupYamlObjects();
	m_ball.reset();
	m_ball.m_score = 0;
	m_ball.m_timer = 120;
	m_ball.m_subtimer = 0;
	m_ball.m_boostUsages = 3;

	m_currentGameState = GameState::PLAYING;
}
