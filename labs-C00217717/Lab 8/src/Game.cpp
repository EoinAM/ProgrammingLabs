#include "Game.h"
#include <iostream>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_height, ScreenSize::s_width, 32), "SFML Playground Lab 3", sf::Style::Default)
	, m_tank(m_texture, m_wallSprites, m_level.m_tank.m_position, m_keyhandler),
	m_aiTank(m_texture, m_wallSprites),
	m_hud(m_font)
{
	m_window.setVerticalSyncEnabled(true);
	if (!m_texture.loadFromFile("./resources/images/SpriteSheet.png"))
	{
		std::string s("Error loading Texture");
		throw std::exception(s.c_str());
	}
	
	int currentLevel = 1;
	if (!LevelLoader::load(currentLevel, m_level))
	{
		return;
	}

	if (!m_font.loadFromFile("./resources/fonts/BlackOpsOne.ttf"))
	{
		std::cout << "font not loaded" << std::endl;
	}
	
	m_bgTexture.loadFromFile(m_level.m_background.m_fileName);
	m_bgSprite.setTexture(m_bgTexture);

	//m_window.setVerticalSyncEnabled(true);
	
	
	generateWalls();
	m_aiTank.init(m_level.m_aiTank.m_position);
}

////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
	

		
}

////////////////////////////////////////////////////////////
void Game::processGameEvents(sf::Event& event)
{
	// check if the event is a a mouse button release
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		m_keyhandler.updateKey(event.key.code, true);
		break;
	case sf::Event::KeyReleased:
		m_keyhandler.updateKey(event.key.code, false);
		break;
	default:
		break;
	}
}

void Game::generateWalls()
{
	sf::IntRect wallRect(2, 129, 33, 23);

	for (ObstacleData const & obstacle : m_level.m_obstacles)
	{
		sf::Sprite sprite;
		sprite.setTexture(m_texture);
		sprite.setTextureRect(wallRect);
		sprite.setOrigin(wallRect.width / 2.0, wallRect.height / 2.0);
		sprite.setPosition(obstacle.m_position);
		sprite.setRotation(obstacle.m_rotation);
		m_wallSprites.push_back(sprite);
	}

}


////////////////////////////////////////////////////////////
void Game::update(double dt)
{

	switch (m_gameState)
	{
	case GameState::GAME_RUNNING:
		m_restartTimer = 0;
		m_tank.update(dt, m_aiTank.m_tankBase);

		if (m_tank.m_AiTankShot)
		{
			m_gameState = GameState::GAME_WIN;
		}
		
		m_aiTank.update(m_tank, dt);
		if (m_aiTank.collidesWithPlayer(m_tank))
		{
			m_gameState = GameState::GAME_LOSE;
		}
		break;
	case GameState::GAME_WIN:
		if (m_restartTimer >= 300)
		{
			for (int i = 0; i < m_tank.m_pool.s_POOL_SIZE; i++)
			{
				m_tank.m_pool.m_projectiles[i].tankCollision = false;	
			}
			m_tank.m_pool.AiTankCollision = false;	
			m_tank.m_AiTankShot = false;

			m_tank.m_tankBase.setPosition(50, 50);
			m_tank.m_turret.setPosition(m_tank.m_tankBase.getPosition());
			m_aiTank.m_tankBase.setPosition(800, 800);

			m_gameState = GameState::GAME_RUNNING;
		}
		else
			m_restartTimer += dt;
		break;
	case GameState::GAME_LOSE:
		if (m_restartTimer >= 300)
		{
			for (int i = 0; i < m_tank.m_pool.s_POOL_SIZE; i++)
			{
				m_tank.m_pool.m_projectiles[i].tankCollision = false;
			}
			m_tank.m_pool.AiTankCollision = false;
			m_tank.m_AiTankShot = false;

			m_tank.m_tankBase.setPosition(50, 50);
			m_tank.m_turret.setPosition(m_tank.m_tankBase.getPosition());
			m_aiTank.m_tankBase.setPosition(800, 800);

			m_gameState = GameState::GAME_RUNNING;
		}
		else
			m_restartTimer += dt;
		break;
	default:
		break;
	}

	m_hud.update(m_gameState);

	
}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
	m_window.draw(m_bgSprite);
	for (auto & obstacle : m_wallSprites)
	{
		m_window.draw(obstacle);
	}
	m_hud.render(m_window);
	m_tank.render(m_window);
	m_aiTank.render(m_window);
	m_window.display();
	
	
}


