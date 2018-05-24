#ifndef PICKUP
#define PICKUP

#include "ScreenSize.h"

#include "SFML\Graphics.hpp"


class PickUp
{
public:
	PickUp();
	~PickUp();
	
	void update(double t_deltaTime);
	void render(sf::RenderWindow & t_window);

	void spawn();

	sf::Sprite getBody();
	sf::Vector2f getPosition();

	bool intersectsCircle(sf::Sprite t_tank);

	bool isDrawn{ true};

	bool m_isAvailable{ false };
private:
	sf::CircleShape m_detectionCircle;
	sf::Sprite m_sprite;
	sf::Vector2f m_position{ 0,0 };

	int m_aliveTimer;
	int m_spawnTimer;

	sf::Texture m_healthTexture;
};

#endif // !PICKUP

