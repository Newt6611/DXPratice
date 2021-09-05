#define main SDL_main

#include <iostream>
#include "World.h"

int main(int argc, char** argv)
{
	
	World* world = World::Create();
	world->Init();

	world->Run();



	delete world;
	return 0;
}