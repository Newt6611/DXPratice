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
class Timer;
class Input;

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
	bool m_WindowShouldClose;
	Display* display = nullptr;
	Renderer* renderer = nullptr;
	Editor* editor = nullptr;
	Timer* timer;

	Ref<ConstantBuffer<PS_PerFrame>> pixel_const;
	DirectionalLight* direction_light;
	PointLight* point_light1;
	PointLight* point_light2;
	PointLight* point_light3;
	PointLight* point_light4;

	std::vector<IGameObject*> m_GameObjects;

	NanoPlayer* nanoPlayer;
	Amoungus* amoungus;
	Sponza* sponza;

	friend class Editor;
};