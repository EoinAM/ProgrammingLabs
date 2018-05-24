/// <summary>
/// @Author Eoin Abbey-Maher
/// </summary>

#include "Block.h"


Block::Block()
{
}

Block::~Block()
{
}

void Block::render(sf::RenderWindow & t_window)
{
	if (m_isShown)
	{
		t_window.draw(m_body);
	}
}
