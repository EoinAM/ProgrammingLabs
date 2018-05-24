#include "Game.h"
#include <iostream>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_height, ScreenSize::s_width, 32), "SFML Playground Lab 3", sf::Style::Default)
	,m_tank(m_texture, m_wallSprites, m_level.m_tank.m_position, m_keyhandler)
{
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

	
	m_bgTexture.loadFromFile(m_level.m_background.m_fileName);
	m_bgSprite.setTexture(m_bgTexture);

	//m_window.setVerticalSyncEnabled(true);
	
	
	generateWalls();

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
	m_tank.update(dt);
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

	m_tank.render(m_window);
	m_window.display();
	
}


