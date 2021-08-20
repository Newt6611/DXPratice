#pragma once
#include "Renderer.h"
#include "../SandBox/NanoPlayer.h"

class IGameObject;

class World
{
	
public:
	World();
	~World();
	void PushGameObjetToWorld(IGameObject* gameObject);
	void Init();
	void Update();
	void Render();

private:
	std::vector<IGameObject*> m_GameObjects;

	NanoPlayer* nanoPlayer;
};