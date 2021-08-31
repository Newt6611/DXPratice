#include "World.h"

#include <string>

#include "IGameObject.h"
#include "Renderer.h"
#include "Display.h"
#include "Editor/Editor.h"
#include "Log.h"
#include "Renderer.h"
#include "DirectionalLight.h"
#include "Timer.h"

World* World::Create()
{
	return new World;
}

World::World()
{
	AllocConsole();
	Log::Init();

	display = Display::Get();
	renderer = Renderer::Get();

	display->Init(1280, 800);
	renderer->Init(this);
	
	editor = new Editor();
	editor->SetWorld(this);
	
	timer = new Timer();

	LogInfo("Engine Start");

	HRESULT result = CoInitialize(NULL);
	if (result != S_OK)
		LogError("Erro CoInit !");

	pixel_const = renderer->CreateConstantBuffer<PS_PerFrame>(ShaderStage::PS);
	direction_light = new DirectionalLight(this, renderer->GetDevice(), renderer->GetContext());

	nanoPlayer = new NanoPlayer(this);
	amoungus = new Amoungus(this);
	//sponza = new Sponza(this);

}

World::~World()
{
	delete display;
	delete renderer;
	delete editor;
	delete timer;

	for (unsigned int i = 0; i < m_GameObjects.size(); i++)
		delete m_GameObjects[i];
}

void World::PushGameObjetToWorld(IGameObject* gameObject)
{
	m_GameObjects.push_back(gameObject);
}

void World::Run()
{
	MSG msg = { };
	while (true)
	{
		if (PeekMessage(&msg, display->GetHandle(), 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) break;
		}

		pixel_const->GetData().eyePos = renderer->GetCamera()->GetPosition();
		pixel_const->Bind(0);

		///////////////     UPDATE      /////////////////////////
		timer->Update();
		Update();
		renderer->Update();

		/////////////////////////////////////////////////////////

		//////////////      Render      ////////////////////////
		renderer->BeginFrame();

		direction_light->Update();

		Render();

		editor->OnImGuiRender();
		renderer->EndFrame();
		////////////////////////////////////////////////////////
	}
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
	// Todo : remove renderer.get camera
	for (unsigned int i = 0; i < m_GameObjects.size(); i++)
		m_GameObjects[i]->Render(renderer->GetCamera());
}