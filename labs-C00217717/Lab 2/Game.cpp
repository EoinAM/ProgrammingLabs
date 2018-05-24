#include "Game.h"
#include <iostream>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

////////////////////////////////////////////////////////////
Game::Game()
	: m_window(sf::VideoMode(ScreenSize::s_height, ScreenSize::s_width, 32), "SFML Playground", sf::Style::Default)
{
	m_window.setVerticalSyncEnabled(true);
	int currentLevel = 1;

	if (!LevelLoader::load(currentLevel, m_level))
	{
		return;
	}


	if (!myTexture.loadFromFile("E-100.png"))
	{
		std::string s("Error loading Texture");
		throw std::exception(s.c_str());
	}

	m_bgTexture.loadFromFile(m_level.m_background.m_fileName);

	m_bgSprite.setTexture(m_bgTexture);

	m_Sprite.setTexture(myTexture);
	m_Sprite.setOrigin(48, 103.5);
	m_Sprite.setRotation(90); //Rotates tank clockwise
	m_Sprite.setPosition(m_level.m_tank.m_position);


	sprite.setTexture(myTexture);

	for (auto &obstacle : m_level.m_obstacles)
	{
		sprite.setPosition(obstacle.m_position);
		sprite.rotate(obstacle.m_rotation);
		m_sprites.push_back(sprite);
	}

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
	if (sf::Event::KeyPressed == event.type)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			m_window.close();
			break;
		case sf::Keyboard::Up:
			// Up key was pressed...
			break;
		default:
			break;
		}
	}
}

////////////////////////////////////////////////////////////
void Game::update(double dt)
{

}

////////////////////////////////////////////////////////////
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0, 0));
	m_window.draw(m_bgSprite);
	for (auto &obstacle : m_sprites)
	{
		m_window.draw(obstacle);
	}
	m_window.draw(m_Sprite);
	m_window.display();
	
}


/// <summary>
/// Exercise Questions
/// 
/// 1.What happens if the sf::texture is put in the .Cpp? The texture doesnt load because it makes it a local variable
/// 
/// 2. where is the sprite drawn, why is part of it missing? The sprite is drawn in the top left corner, The origin is in the middle of the texture no so it only shows a quarter.
/// 
/// 3. How can the rotated tank be fixed? Rotate the texture before bringing it into visual studio so it loads in facing right
/// </summary>


