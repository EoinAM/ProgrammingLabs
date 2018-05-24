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
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 


#pragma comment(lib,"thor-d.lib")
#pragma comment(lib, "thor.lib")
#pragma comment(lib,"libyaml-cppmdd") 
#include "Game.h"

/// <summary>
/// @brief starting point for all C++ programs.
/// 
/// Create a game object and run it.
/// </summary>
/// <param name=""></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int, char* argv[])
{
	Game game;
	game.run();
}


/// <summary>
/// Questions
/// 1.Does the tank move to the keyboard inputs?
/// 1. Not at first have to update position in the tank update and then call it in the game update
/// 
/// 2.What happens the turret?
/// 2. the turret stays in the top corner whilst the base moves away
/// 
/// 3. what happens the turret when the base rotates?
/// 3. The turret doesnt change rotation
/// 
/// </summary>