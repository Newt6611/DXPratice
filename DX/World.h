#pragma once
#include "../SandBox/NanoPlayer.h"
#include "../SandBox/Amoungus.h"
#include "../SandBox/Sponza.h"
#include "Base.h"
class Texture;
class Renderer;
class Display;
class IGameObject;
class Editor;
class DirectionalLight;

class World
{

public:
	static World* Create();
	World();
	~World();
	void PushGameObjetToWorld(IGameObject* gameObject);
	void Run();
	void Init();
	void Update();
	void Render();

private:


private:
	Display* display = nullptr;
	Renderer* renderer = nullptr;
	Editor* editor = nullptr;

	//Ref<Texture> t;

	Ref<ConstantBuffer<PS_PerFrame>> pixel_const;
	DirectionalLight* direction_light;

	std::vector<IGameObject*> m_GameObjects;

	NanoPlayer* nanoPlayer;
	Amoungus* amoungus;
	Sponza* sponza;

	friend class Editor;
};