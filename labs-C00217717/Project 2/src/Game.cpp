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

	if (!m_font.loadFromFile("./resources/fonts/Carnevalee Freakshow.ttf"))
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

		m_aiTank.update(m_tank, dt, m_healthPickUp);
		if (m_aiTank.collidesWithPlayer(m_tank))
		{
			m_gameState = GameState::GAME_LOSE;
		}

		if (CollisionDetector::collision(m_tank.m_pool.getActive().m_projectile, m_aiTank.m_tankBase) && m_aiShotTimer <= 0)
		{
	       		m_aiTank.m_health -= 10;
				m_aiShotTimer = 1000;
		}

		if (CollisionDetector::collision(m_aiTank.m_pool.getActive().m_projectile, m_tank.m_tankBase) && m_tankShotTimer <= 0)
		{
			m_tank.m_health -= 5;
			m_tankShotTimer = 1000;
		}

		m_aiShotTimer -= dt;
		m_tankShotTimer -= dt;
		if (CollisionDetector::collision(m_aiTank.m_tankBase, m_healthPickUp.getBody()) && m_healthPickUp.m_isAvailable)
		{
			if (m_aiTank.m_health < 50)
			{
				m_aiTank.m_health = 50;
			}
			else if (m_aiTank.m_health < 90 && m_aiTank.m_health > 50)
			{
				m_aiTank.m_health += 10;
			}
			else
			{
				m_aiTank.m_health = 100;
			}
			
			m_healthPickUp.isDrawn = false;
			m_healthPickUp.m_isAvailable = false;
			m_aiTank.m_aiBehaviour = TankAi::AiBehaviour::SEEK_PLAYER;
		}

		if (CollisionDetector::collision(m_tank.m_tankBase, m_healthPickUp.getBody()) && m_healthPickUp.m_isAvailable)
		{
			if (m_tank.m_health <= 75)
			{
				m_tank.m_health += 15;
			}
			else m_tank.m_health = 100;
			m_healthPickUp.isDrawn = false;
			m_healthPickUp.m_isAvailable = false;
		}

		if (m_aiTank.m_health <= 0)
		{
			m_gameState = GameState::GAME_WIN;
		}

		if (m_tank.m_health <= 0)
		{
			m_gameState = GameState::GAME_LOSE;
		}
		if (m_healthPickUp.intersectsCircle(m_aiTank.m_tankBase) || m_healthPickUp.intersectsCircle(m_tank.m_tankBase))
		{
			m_healthPickUp.isDrawn = true;
			std::cout << "intersecting health" << std::endl;
		}
		else if(!m_healthPickUp.intersectsCircle(m_aiTank.m_tankBase) || !m_healthPickUp.intersectsCircle(m_tank.m_tankBase))
		{
			m_healthPickUp.isDrawn = false;
		}

		m_healthPickUp.update(dt);
		break;
	case GameState::GAME_WIN:
		if (m_restartTimer >= 3000)
		{
			m_tank.m_tankBase.setPosition(50, 50);
			m_tank.m_turret.setPosition(m_tank.m_tankBase.getPosition());
			m_aiTank.m_tankBase.setPosition(800, 800);
			m_tank.m_health = 100;
			m_aiTank.m_health = 100;

			m_gameState = GameState::GAME_RUNNING;
		}
		else
			m_restartTimer += dt;
		break;
	case GameState::GAME_LOSE:
		if (m_restartTimer >= 3000)
		{
			m_tank.m_tankBase.setPosition(50, 50);
			m_tank.m_turret.setPosition(m_tank.m_tankBase.getPosition());
			m_aiTank.m_tankBase.setPosition(800, 800);
			m_tank.m_health = 100;
			m_aiTank.m_health = 100;

			m_gameState = GameState::GAME_RUNNING;
		}
		else
			m_restartTimer += dt;
		break;
	default:
		break;
	}

	m_hud.update(m_gameState, m_tank, m_aiTank, m_healthPickUp);
	
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
	m_healthPickUp.render(m_window);
	m_tank.render(m_window);
	m_aiTank.render(m_window);
	m_window.display();
	
	
}


