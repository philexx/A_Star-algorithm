#include "Game.h"


int main(int argc, char* args[])
{
	cFramerwork::Get()->Init();
	cGame Game;
	Game.Init();
	Game.Run();
	Game.Del();
	cFramerwork::Get()->Terminate();
	cFramerwork::Get()->Delete(); //Delete the Framework Singleton 
	cTimer::Get()->Delete();
	return 0;
}