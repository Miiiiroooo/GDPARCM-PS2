#include <iostream>
#include "Game.h"

int main()
{
	Game::GetInstance()->Initialize();
	Game::GetInstance()->Run();

	return 0;
}