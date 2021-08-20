#include "World.h"
#include "IGameObject.h"


World::World()
{
	nanoPlayer = new NanoPlayer(this);
}

World::~World()
{
	for (unsigned int i = 0; i < m_GameObjects.size(); i++)
		delete m_GameObjects[i];
}

void World::PushGameObjetToWorld(IGameObject* gameObject)
{
	m_GameObjects.push_back(gameObject);
}

void World::Init()
{
	for (unsigned int i = 0; i < m_GameObjects.size(); i++)
		m_GameObjects[i]->Init();
}

void World::Update()
{
	for (unsigned int i = 0; i < m_GameObjects.size(); i++)
		m_GameObjects[i]->Update();
}

void World::Render()
{
	for (unsigned int i = 0; i < m_GameObjects.size(); i++)
		m_GameObjects[i]->Render();
}
