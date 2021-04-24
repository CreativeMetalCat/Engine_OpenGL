#define USE_DEFAULT_CPP
#include "Game.h"

int main()
{
	Engine::CGame* game = new Engine::CGame();
	game->CreateWindow("game");
	game->Run();

	return 0;
}