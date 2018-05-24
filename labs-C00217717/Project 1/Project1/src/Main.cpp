/// <summary>
/// @Author Eoin Abbey-Maher
/// @Date November 2017
/// @Brief Mini Project 1 
///		create a cross between Spacer Invaders and Arkanoid
/// 
/// Known Issues:	
///				 Collisions dont always work as intended,
///				 No Extra Feature,
///				 Game doesnt end when all blocks are destroyed,
///				 Blocks do not always dissapear when collided with,
///				 Power Up sometimes changes direction of Ball,
///					 
/// </summary>

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#pragma comment(lib,"libyaml-cppmdd")

#include "Game.h"


int main(int, char * argv[])
{
	Game game;
	game.run();
}
