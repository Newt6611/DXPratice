#pragma once
#include "../SandBox/NanoPlayer.h"
#include "Base.h"
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


	Ref<ConstantBuffer<PS_PerFrame>> pixel_const;
	//Ref<DirectionalLight> direction_light;
	DirectionalLight* direction_light;

	std::vector<IGameObject*> m_GameObjects;

	NanoPlayer* nanoPlayer;
	NanoPlayer* playertwo;

	friend class Editor;
};