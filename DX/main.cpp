#include <iostream>
#include "World.h"

int main()
{
	
	World* world = World::Create();
	world->Init();

	world->Run();



	delete world;
}