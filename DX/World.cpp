#include "World.h"

#include <string>

#include "IGameObject.h"
#include "Renderer.h"
#include "Display.h"
#include "Editor/Editor.h"
#include "Log.h"
#include "Renderer.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Timer.h"
#include "Input.h"

World* World::Create()
{
	return new World;
}

World::World()
{
	//AllocConsole();
	Log::Init();

	display = Display::Get();
	renderer = Renderer::Get();

	display->Init(1280, 800);
	renderer->Init(this);
	
	editor = new Editor();
	editor->SetWorld(this);
	
	timer = new Timer();

	LogInfo("Engine Start");


	pixel_const = renderer->CreateConstantBuffer<PS_PerFrame>(ShaderStage::PS);
	direction_light = new DirectionalLight(this, renderer->GetDevice(), renderer->GetContext());

	point_light1 = new PointLight(this, renderer->GetDevice(), renderer->GetContext());
	point_light2 = new PointLight(this, renderer->GetDevice(), renderer->GetContext());
	point_light3 = new PointLight(this, renderer->GetDevice(), renderer->GetContext());
	point_light4 = new PointLight(this, renderer->GetDevice(), renderer->GetContext());


	nanoPlayer = new NanoPlayer(this);
	amoungus = new Amoungus(this);
	sponza = new Sponza(this);
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
	while (!m_WindowShouldClose)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				m_WindowShouldClose = true;
			if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE && e.window.windowID == SDL_GetWindowID(display->GetWindow()))
				m_WindowShouldClose = true;
			if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED)
				display->OnResize();

			Input::mouseWheelY = e.wheel.y;
			Input::Update();
		}

	
		pixel_const->GetData().eyePos = renderer->GetCamera()->GetPosition();
		pixel_const->GetData().d_Light = direction_light->GetLightData();
		pixel_const->GetData().p_Light[0] = point_light1->GetLightData();
		pixel_const->GetData().p_Light[1] = point_light2->GetLightData();
		pixel_const->GetData().p_Light[2] = point_light3->GetLightData();
		pixel_const->GetData().p_Light[3] = point_light4->GetLightData();
		pixel_const->Bind(0);
	
		///////////////     UPDATE      /////////////////////////
		renderer->GetCamera()->Update();
		timer->Update();
		Update();
		renderer->Update();
	
		/////////////////////////////////////////////////////////
	
		//////////////      Render      ////////////////////////
		renderer->BeginFrame();
		
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

	point_light2->SetName("P2");
	point_light3->SetName("P3");
	point_light4->SetName("P4");

	point_light1->SetPosition(XMFLOAT3(0, -3, 0));
	point_light2->SetPosition(XMFLOAT3(5, -3, 0));
	point_light3->SetPosition(XMFLOAT3(-8, -3, 5));
	point_light4->SetPosition(XMFLOAT3(0, -3, 10));

	direction_light->SetAmbient(XMFLOAT3(0, 0, 0));
	direction_light->SetDiffuse(XMFLOAT3(0, 0, 0));
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